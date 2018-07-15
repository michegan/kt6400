#include <QtDebug>

#ifndef _WIN32
    #include <errno.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
#endif

#include "halfpga.h"
#include "utility.h"
#include "libinter.h"


// FPGAͨ��
namespace HalFpga
{
    // �豸���
    static int s_fd = -1;

    // ��ʼ��
    bool init()
    {
#ifdef _WIN32
        qDebug() << "HalFpga init";
        return true;
#else 

        s_fd = open("/dev/int_device", O_RDWR | O_NDELAY);
        qDebug() << "HalFpga init" << s_fd;

        // SYSDRVDATAINT��C����ʵ�֣��޷���C++�е��ã���������SysDrvDataInit��ɹ���
        SysDrvDataInit(s_fd);

        if (0 < s_fd)
        {
            // FD����
            fcntl(s_fd, F_SETOWN, getpid());

            int oflag = fcntl(s_fd, F_GETFL);
            fcntl(s_fd, F_SETFL, oflag | FASYNC);
        }

        return (0 < s_fd);
#endif
    }

    // FPGAд
    bool write(int cmd)
    {
        return HalFpga::write(cmd, 0);
    }

    bool write(int cmd, unsigned char para)
    {
        bool ret = false;

#ifdef _WIN32
        ret = true;
#else 
        ret = (0 <= ioctl(s_fd, cmd, para));
#endif

        qDebug() << "HalFpga write" << cmd << para << ret;

        return ret;
    }

    bool write_addr(int cmd, int para)
    {
        bool ret = false;

#ifdef _WIN32
        ret = true;
#else 
        ret = (0 <= ioctl(s_fd, cmd, para));
#endif

        qDebug() << "HalFpga write_addr" << cmd << para << ret;

        return ret;
    }

    // FPGA��
    bool query(int cmd, char* buffer, int len)
    {
#ifndef _WIN32
        if (HalFpga::write(cmd))
        {
            // ��ʱ50ms���ȴ����ݿɶ�
            Utility::msleep(50);

            read(s_fd, buffer, len);
        }
#endif 
        
        return true;
    }
}