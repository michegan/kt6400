#include <QtDebug>

#include "halnetlink.h"


// NETLINKͨ��
namespace HalNetlink
{
    // �ⲿ��ӡ����
    int create_lp_kernel_sock()
    {
        qDebug() << "HalNetlink create_lp_kernel_sock";
        return 0;
    }

    // WBC HGB ���ݲɼ���
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
