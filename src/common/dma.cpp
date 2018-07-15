#include <QtDebug>

#include "dma.h"


namespace Dma
{
    // ��ʼ��
    void init()
    {
        qDebug() << "Dma init";

        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            dmaBuf->hgbAdVoltage = 0;
            dmaBuf->hgbBkVoltage = 0;

            dmaBuf->wbcSamplingBufLen = 0;
            dmaBuf->rbcSamplingBufLen = 0;
            dmaBuf->pltSamplingBufLen = 0;
        }
    }

    // ȫ��DMA������
    DmaBuf* getDmaBuf()
    {
        static DmaBuf* s_dmaBuf = 0;
        if (0 == s_dmaBuf)
        {
            s_dmaBuf = new DmaBuf();
        }
        return s_dmaBuf;
    }
}