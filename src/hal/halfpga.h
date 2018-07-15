#ifndef _HAL_FPGA_H_
#define _HAL_FPGA_H_


#include "libhal.h"


// FPGAͨ��
namespace HalFpga
{
    // ��ʼ��
    HAL_EXPORT bool init();

    // FPGAд
    HAL_EXPORT bool write(int cmd);
    HAL_EXPORT bool write(int cmd, unsigned char para);

    HAL_EXPORT bool write_addr(int cmd, int para);

    // FPGA��
    HAL_EXPORT bool query(int cmd, char* buffer, int len);
};


#endif // _HAL_FPGA_H_
