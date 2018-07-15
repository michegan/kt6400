#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include <QtDebug>

#include "serial.h"


class SerialPrivate
{
public:
    SerialPrivate();
    ~SerialPrivate();

    // 打开设备
    bool s_open(const QString& name, int baudrate, int databits);

    // 关闭设备
    void s_close();

public:
    // 设备句柄
    int fd;
};

SerialPrivate::SerialPrivate()
    : fd(-1)
{

}

SerialPrivate::~SerialPrivate()
{
    this->s_close();
}

// 打开设备
bool SerialPrivate::s_open(const QString &name, int baudrate, int databits)
{
    bool ret = false;

    do 
    {
        // 打开设备
        this->fd = open(name.toAscii().constData(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (this->fd < 0)
        {
            qWarning() << "SerialPrivate s_open open fail";
            break;
        }

        // 初始化
        struct termios opt;

        tcflush(this->fd, TCOFLUSH);
        tcflush(this->fd, TCIFLUSH);

        // 获取设备termios结构
        if (tcgetattr(this->fd, &opt) < 0)
        {
            qWarning() << "SerialPrivate s_open tcgetattr fail";
            break;
        }

        // 设置波特率
        cfsetispeed(&opt, baudrate);
        cfsetospeed(&opt, baudrate);

        // 控制标志：8位数据位、无校验位
        opt.c_cflag &= ~(CSTOPB | CSIZE | PARENB);
        opt.c_cflag |= CS8;
        opt.c_cflag |= (CLOCAL | CREAD);

        // 输入标志
        opt.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        // 输出标志
        opt.c_oflag &= ~(OPOST);

        // 本地标志：原始模式
        opt.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

        // VMIN:需读取的最小字节数 VTIME:限定的传输或等待的最长时间
        opt.c_cc[VMIN] = 1; // 一次read调用期望返回的最小字节数
        opt.c_cc[VTIME] = 0; // 150表示15秒

        // 设置
        if (tcsetattr(this->fd, TCSANOW, &opt) < 0)
        {
            qWarning() << "SerialPrivate s_open tcsetattr fail";
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

// 关闭设备
void SerialPrivate::s_close()
{
    if (0 < this->fd)
    {
        close(this->fd);
        this->fd = -1;
    }
}


Serial::Serial()
    : d(new SerialPrivate())
{

}

Serial::~Serial()
{
    delete d;
}

// 打开设备
bool Serial::open(const QString &name, int baudrate, int databits)
{
    qDebug() << "Serial open" << name << baudrate << databits;

    return d->s_open(name, baudrate, databits);
}

// 关闭设备
void Serial::close()
{
    d->s_close();
}

// 数据接收
int Serial::readData(char* data, int maxSize)
{
    char* p = data;
    int nleft = maxSize;

    while (0 < nleft)
    {
        int nread = read(d->fd, p, nleft);
        if (0 < nread)
        {
            p += nread;
            nleft -= nread;
        }
        else
        {
            break;
        }
    }

    return (maxSize - nleft);
}

// 数据发送
int Serial::sendData(const char* data, int maxSize)
{
    return write(d->fd, data, maxSize);
}

