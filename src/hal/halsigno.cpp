#include <QtDebug>

#ifndef _WIN32
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/mman.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/signal.h>
#endif

#include "halfpga.h"
#include "halsigno.h"


// SIGNOͨ��
namespace HalSigno
{
    static void Sys_Sampling_Data_Copy(int signo)
    {
        qDebug() << "HalSigno Sys_Sampling_Data_Copy" << signo;

        //SYS_TIMER* pTimer = (SYS_TIMER*)GETTIMER();

        //if (pTimer->timer[5] == HGB_BK_MODULE)
        //{
        //    int hgbB = 0;
        //    HalFpga::query(&hgbB, sizeof(int));
        //}
        //else if (pTimer->timer[5] == HGB_AD_MODULE)
        //{
        //    int hgbT = 0;
        //    HalFpga::query(&hgbB, sizeof(int));
        //}
    }

    // ��ʼ��
    bool init()
    {
        int ret = 0;

        qDebug() << "HalSigno init";

#ifndef _WIN32
        struct sigaction sigact, oldact;

        // ��ʼ���źż���Ϊ��
        // .sa_mask�����������ڴ�����ź�ʱ��ʱ��sa_maskָ�����źŸ���
        sigemptyset(&sigact.sa_mask);

        // .sa_flags�����������źŴ����������ز���
        sigact.sa_flags = SA_INTERRUPT;
        sigact.sa_handler = Sys_Sampling_Data_Copy;

        ret = sigaction(SIGIO, &sigact, &oldact);
#endif

        return (0 < ret);
    }
}