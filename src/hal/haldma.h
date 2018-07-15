#ifndef _HAL_DMA_H_
#define _HAL_DMA_H_


#include "libhal.h"


// 数据采集缓冲区
#define SAMPLING_BUF_LEN        (10 * 1024 * 1024)


// DMA通信
namespace HalDma
{
    // 初始化
    HAL_EXPORT bool init();
};


#endif // _HAL_DMA_H_