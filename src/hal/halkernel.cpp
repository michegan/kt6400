#include <QtDebug>

#ifndef _WIN32
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
#endif

#include "halkernel.h"


// FPGA通信
namespace HalKernel
{
    // 触摸屏校准值
    bool setTsValue(int value, int count)
    {
        bool ret = false;

        do 
        {
#ifndef _WIN32
            int fd = open("/dev/TS_IOCTL", O_RDWR);
            if (fd < 0)
            {
                qWarning() << "HalKernel setTsValue open fail";
                break;
            }

            if (ioctl(fd, 0, &value) < 0)
            {
                qWarning() << "HalKernel setTsValue ioctl value fail";
                break;
            }

            if (ioctl(fd, 1, &count) < 0)
            {
                qWarning() << "HalKernel setTsValue ioctl count fail";
                break;
            }

            close(fd);
#endif
            ret = true;
        } while (0);

        return ret;
    }
}
