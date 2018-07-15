#ifndef _DMA_H_
#define _DMA_H_


#include "libcommon.h"


// DMA������
struct DmaBuf
{
    int wbcSamplingBufLen; // WBCͨ������
    char* pWbcSamplingBuf; // WBCͨ����ʼ��ַ

    int rbcSamplingBufLen; // RBCͨ������
    char* pRbcSamplingBuf; // RBCͨ����ʼ��ַ

    int pltSamplingBufLen; // RBCͨ������
    char* pPltSamplingBuf; // PLTͨ����ʼ��ַ

    unsigned int hgbAdVoltage; // HGB������ѹ
    unsigned int hgbBkVoltage; // HGB���׵�ѹ
};


namespace Dma
{
    // ��ʼ��
    COMMON_EXPORT void init();

    // ȫ��DMA������
    COMMON_EXPORT DmaBuf* getDmaBuf();
}


#endif // _DMA_H_