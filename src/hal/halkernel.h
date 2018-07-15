#ifndef _HAL_KERNEL_H_
#define _HAL_KERNEL_H_


#include "libhal.h"


// KERNEL通信
namespace HalKernel
{
    // 触摸屏校准值
    HAL_EXPORT bool setTsValue(int value, int count);
};


#endif // _HAL_KERNEL_H_
