#ifndef _HAL_DMA_H_
#define _HAL_DMA_H_


#include "libhal.h"


// ���ݲɼ�������
#define SAMPLING_BUF_LEN        (10 * 1024 * 1024)


// DMAͨ��
namespace HalDma
{
    // ��ʼ��
    HAL_EXPORT bool init();
};


#endif // _HAL_DMA_H_