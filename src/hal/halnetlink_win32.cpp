#include <QtDebug>

#include "halnetlink.h"


// NETLINK通信
namespace HalNetlink
{
    // 外部打印机用
    int create_lp_kernel_sock()
    {
        qDebug() << "HalNetlink create_lp_kernel_sock";
        return 0;
    }

    // WBC HGB 数据采集用
    int init_wh_sock()
    {
        qDebug() << "HalNetlink init_wh_sock";
        return 0;
    }

    int recv_whmsg_from_drv()
    {
        qDebug() << "HalNetlink recv_whmsg_from_drv";
        return 0;
    }
}
