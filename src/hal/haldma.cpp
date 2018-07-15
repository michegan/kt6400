#include <QtDebug>

#ifndef _WIN32
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/mman.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
#endif

#include "dma.h"
#include "haldma.h"


// DMAͨ��
namespace HalDma
{
    // ��ʼ��
    bool init()
    {
        bool ret = false;

        qDebug() << "HalDma init";

        do 
        {
#ifdef _WIN32
            // �����䵽���ڴ��ֵ�󶨵�ȫ�ֱ�����
            DmaBuf* dmaBuf = Dma::getDmaBuf();
            if (dmaBuf)
            {
                dmaBuf->wbcSamplingBufLen = 0;
                dmaBuf->rbcSamplingBufLen = 0;
                dmaBuf->pltSamplingBufLen = 0;

                dmaBuf->pWbcSamplingBuf = new char[SAMPLING_BUF_LEN];
                dmaBuf->pRbcSamplingBuf = new char[SAMPLING_BUF_LEN];
                dmaBuf->pPltSamplingBuf = new char[SAMPLING_BUF_LEN];
            }

#else
            // �����ڴ��豸�ļ�
            int fd = open("/dev/mem", O_RDONLY);
            if (fd < 0)
            {
                qWarning() << "HalDma init open fail";
                break;
            }

            // �����ڴ��ڴ�ӳ��
            char* address = (char*)mmap(NULL, 0x1E00000, PROT_READ, MAP_PRIVATE, fd, 0x5acf9000);
            if (0 == address)
            {
                qWarning() << "HalDma init mmap fail";
                break;
            }

            qDebug() << "HalDma init" << fd << (int)address;

            // �����䵽���ڴ��ֵ�󶨵�ȫ�ֱ�����
            DmaBuf* dmaBuf = Dma::getDmaBuf();
            if (dmaBuf)
            {
                dmaBuf->wbcSamplingBufLen = 0;
                dmaBuf->rbcSamplingBufLen = 0;
                dmaBuf->pltSamplingBufLen = 0;

                dmaBuf->pWbcSamplingBuf = address;
                dmaBuf->pRbcSamplingBuf = address + SAMPLING_BUF_LEN;
                dmaBuf->pPltSamplingBuf = address + 2 * SAMPLING_BUF_LEN;
            }

#endif

            ret = true;
        } while (0);

        return ret;
    }
}