#ifndef _DMA_H_
#define _DMA_H_


#include "libcommon.h"


// DMA缓冲区
struct DmaBuf
{
    int wbcSamplingBufLen; // WBC通道长度
    char* pWbcSamplingBuf; // WBC通道起始地址

    int rbcSamplingBufLen; // RBC通道长度
    char* pRbcSamplingBuf; // RBC通道起始地址

    int pltSamplingBufLen; // RBC通道长度
    char* pPltSamplingBuf; // PLT通道起始地址

    unsigned int hgbAdVoltage; // HGB测量电压
    unsigned int hgbBkVoltage; // HGB本底电压
};


namespace Dma
{
    // 初始化
    COMMON_EXPORT void init();

    // 全局DMA缓冲区
    COMMON_EXPORT DmaBuf* getDmaBuf();
}


#endif // _DMA_H_