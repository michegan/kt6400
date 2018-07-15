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


// FPGA通信
namespace HalFpga
{
    // 设备句柄
    static int s_fd = -1;

    // 初始化
    bool init()
    {
#ifdef _WIN32
        qDebug() << "HalFpga init";
        return true;
#else 

        s_fd = open("/dev/int_device", O_RDWR | O_NDELAY);
        qDebug() << "HalFpga init" << s_fd;

        // SYSDRVDATAINT是C语言实现，无法在C++中调用，所以新增SysDrvDataInit完成过渡
        SysDrvDataInit(s_fd);

        if (0 < s_fd)
        {
            // FD配置
            fcntl(s_fd, F_SETOWN, getpid());

            int oflag = fcntl(s_fd, F_GETFL);
            fcntl(s_fd, F_SETFL, oflag | FASYNC);
        }

        return (0 < s_fd);
#endif
    }

    // FPGA写
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

    // FPGA读
    bool query(int cmd, char* buffer, int len)
    {
#ifndef _WIN32
        if (HalFpga::write(cmd))
        {
            // 延时50ms，等待数据可读
            Utility::msleep(50);

            read(s_fd, buffer, len);
        }
#endif 
        
        return true;
    }
}