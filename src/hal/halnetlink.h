#ifndef _HAL_NETLINK_H_
#define _HAL_NETLINK_H_


#include "libhal.h"


// NETLINKͨ��
namespace HalNetlink
{
    // �ⲿ��ӡ����
    HAL_EXPORT int create_lp_kernel_sock();

    // WBC HGB ���ݲɼ���
    HAL_EXPORT int init_wh_sock();
    HAL_EXPORT int recv_whmsg_from_drv();
};


#endif // _HAL_NETLINK_H_