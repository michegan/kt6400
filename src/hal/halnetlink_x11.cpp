#include <QtDebug>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "dma.h"
#include "halnetlink.h"

#define WBC_MODULE         50
#define RBC_MODULE         100
#define HGB_BK_MODULE      300
#define HGB_AD_MODULE      350

#define  INIT_LP_MSG  0
#define  LP_ADD_MSG   1
#define  PAPER_MSG    2
#define  REMOVE_MSG   3

#define MAX_PAYLOAD 32

#define NETLINK_INIT_INQ 10 
#define NETLINK_LP_MSG 21
#define NETLINK_WBC_DATA 22


// NETLINK通信
namespace HalNetlink
{
    // 外部打印机用
    static int s_lp_fd = -1;
    int create_lp_kernel_sock()
    {
        qDebug() << "HalNetlink create_lp_kernel_sock";

        struct msg_to_kernel
        {
            struct nlmsghdr hdr;
        };

        s_lp_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_LP_MSG);
        if (s_lp_fd < 0)
        {
            qWarning() << "HalNetlink create_lp_kernel_sock socket fail";
            return -1;
        }

        struct sockaddr_nl local;
        memset(&local, 0, sizeof(local));
        local.nl_family = AF_NETLINK;
        local.nl_pid = getpid();
        local.nl_groups = 0;

        int ret = bind(s_lp_fd, (struct sockaddr*)&local, sizeof(local));
        if (0 != ret)
        {
            close(s_lp_fd);
            qWarning() << "HalNetlink create_lp_kernel_sock bind fail";
            return -1;
        }

        struct sockaddr_nl kpeer;

        memset(&kpeer, 0, sizeof(kpeer));
        kpeer.nl_family = AF_NETLINK;
        kpeer.nl_pid = 0;
        kpeer.nl_groups = 0;

        struct msg_to_kernel message;
        memset(&message, 0, sizeof(message));
        message.hdr.nlmsg_len = NLMSG_LENGTH(0);
        message.hdr.nlmsg_flags = 0;
        message.hdr.nlmsg_type = INIT_LP_MSG;
        message.hdr.nlmsg_pid = local.nl_pid;

        ret = sendto(s_lp_fd, &message, message.hdr.nlmsg_len, 0, (struct sockaddr*)&kpeer, sizeof(kpeer));
        qDebug() << "HalNetlink create_lp_kernel_sock sendto" << ret;

        return 0;
    }


    // WBC HGB 数据采集用
    int  wbc_sock_fd;
    struct sockaddr_nl wh_local;
    struct sockaddr_nl wh_kpeer;
    struct nlmsghdr *wbc_nlh = NULL;
    struct iovec wbc_iov;
    struct msghdr wbc_message;

    int init_wh_sock()
    {
        int retval;
        int state_smg = 0;

        qDebug() << "HalNetlink init_wh_sock";

        wbc_sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_WBC_DATA);
        if(wbc_sock_fd < 0)
        {
            qWarning() << "HalNetlink init_wh_sock socket fail";
            return -1;
        }

        // To prepare binding
        memset(&wbc_message,0,sizeof(wbc_message));
        memset(&wh_local, 0, sizeof(wh_local));
        wh_local.nl_family = AF_NETLINK;
        wh_local.nl_pid = getpid(); // self pid
        wh_local.nl_groups = 0; // multi cast


        retval = bind(wbc_sock_fd, (struct sockaddr*)&wh_local, sizeof(wh_local));
        if(retval < 0)
        {
            qWarning() << "HalNetlink init_wh_sock bind fail";
            close(wbc_sock_fd);
            return -1;
        }

        // To prepare recvmsg
        wbc_nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
        if(!wbc_nlh)
        {
            qWarning() << "HalNetlink init_wh_sock malloc fail";
            close(wbc_sock_fd);
            return -1;
        }

        memset(&wh_kpeer,0,sizeof(wh_kpeer));
        wh_kpeer.nl_family = AF_NETLINK;
        wh_kpeer.nl_pid = 0;
        wh_kpeer.nl_groups = 0;

        wbc_nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
        wbc_nlh->nlmsg_pid = getpid();
        wbc_nlh->nlmsg_flags = 0;
        wbc_nlh->nlmsg_type = NETLINK_INIT_INQ;     /*设置自定义消息类型*/

        wbc_iov.iov_base = (void *)wbc_nlh;
        wbc_iov.iov_len = NLMSG_SPACE(MAX_PAYLOAD); 

        memset(&wbc_message, 0, sizeof(wbc_message));

        wbc_message.msg_name = (void *)&wh_kpeer;
        wbc_message.msg_namelen = sizeof(wh_kpeer);
        wbc_message.msg_iov = &wbc_iov;
        wbc_message.msg_iovlen = 1;

        printf("Send WBC message to dev\n");
        state_smg = sendmsg(wbc_sock_fd,&wbc_message,0);

        if(state_smg == -1)
        {
            qWarning() << "HalNetlink init_wh_sock sendmsg fail";
        }

        return 0;
    }

    /*********************************************************************************************
                                    接收WBC、HGB采样数据
    *********************************************************************************************/
    int recv_whmsg_from_drv()
    {
        int rcvlen = 0;

        memset(wbc_nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));

        /*接收内核空间返回的数据*/
        rcvlen = recvmsg(wbc_sock_fd, &wbc_message, MSG_DONTWAIT);
        qDebug() << "HalNetlink recv_whmsg_from_drv" << rcvlen;

        /*处理接收到的数据*/
        if( rcvlen > 0 )
        {
            if( wbc_nlh->nlmsg_type == WBC_MODULE )
            {
                qDebug() << "HalNetlink recv_whmsg_from_drv WBC_MODULE";
            }  
            else if( wbc_nlh->nlmsg_type == HGB_BK_MODULE)  
            {
                qDebug() << "HalNetlink recv_whmsg_from_drv HGB_BK_MODULE";

                unsigned char TempHgbAdBuf[2] = { 0 };
                memcpy(TempHgbAdBuf, (unsigned char*)(NLMSG_DATA(wbc_nlh)), 2);

                DmaBuf* dmaBuf = Dma::getDmaBuf();
                if (dmaBuf)
                {
                    dmaBuf->hgbBkVoltage = (TempHgbAdBuf[0] | (TempHgbAdBuf[1] << 8));

                    qDebug() << "HalNetlink recv_whmsg_from_drv hgbBkVoltage" << dmaBuf->hgbBkVoltage;
                }
            } 
            else if( wbc_nlh->nlmsg_type == HGB_AD_MODULE )  
            {
                qDebug() << "HalNetlink recv_whmsg_from_drv HGB_AD_MODULE";

                unsigned char TempHgbAdBuf[2] = { 0 };
                memcpy(TempHgbAdBuf, (unsigned char*)(NLMSG_DATA(wbc_nlh)), 2);

                DmaBuf* dmaBuf = Dma::getDmaBuf();
                if (dmaBuf)
                {
                    dmaBuf->hgbAdVoltage = (TempHgbAdBuf[0] | (TempHgbAdBuf[1] << 8));

                    qDebug() << "HalNetlink recv_whmsg_from_drv hgbAdVoltage" << dmaBuf->hgbAdVoltage;
                }
            }
            else
            {
                qWarning() << "HalNetlink recv_whmsg_from_drv invalid nlmsg_type" << wbc_nlh->nlmsg_type;
            }
        }

        return rcvlen;
    }
}
