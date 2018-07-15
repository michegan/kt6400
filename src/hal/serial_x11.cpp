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

    // ���豸
    bool s_open(const QString& name, int baudrate, int databits);

    // �ر��豸
    void s_close();

public:
    // �豸���
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

// ���豸
bool SerialPrivate::s_open(const QString &name, int baudrate, int databits)
{
    bool ret = false;

    do 
    {
        // ���豸
        this->fd = open(name.toAscii().constData(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (this->fd < 0)
        {
            qWarning() << "SerialPrivate s_open open fail";
            break;
        }

        // ��ʼ��
        struct termios opt;

        tcflush(this->fd, TCOFLUSH);
        tcflush(this->fd, TCIFLUSH);

        // ��ȡ�豸termios�ṹ
        if (tcgetattr(this->fd, &opt) < 0)
        {
            qWarning() << "SerialPrivate s_open tcgetattr fail";
            break;
        }

        // ���ò�����
        cfsetispeed(&opt, baudrate);
        cfsetospeed(&opt, baudrate);

        // ���Ʊ�־��8λ����λ����У��λ
        opt.c_cflag &= ~(CSTOPB | CSIZE | PARENB);
        opt.c_cflag |= CS8;
        opt.c_cflag |= (CLOCAL | CREAD);

        // �����־
        opt.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        // �����־
        opt.c_oflag &= ~(OPOST);

        // ���ر�־��ԭʼģʽ
        opt.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

        // VMIN:���ȡ����С�ֽ��� VTIME:�޶��Ĵ����ȴ����ʱ��
        opt.c_cc[VMIN] = 1; // һ��read�����������ص���С�ֽ���
        opt.c_cc[VTIME] = 0; // 150��ʾ15��

        // ����
        if (tcsetattr(this->fd, TCSANOW, &opt) < 0)
        {
            qWarning() << "SerialPrivate s_open tcsetattr fail";
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

// �ر��豸
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

// ���豸
bool Serial::open(const QString &name, int baudrate, int databits)
{
    qDebug() << "Serial open" << name << baudrate << databits;

    return d->s_open(name, baudrate, databits);
}

// �ر��豸
void Serial::close()
{
    d->s_close();
}

// ���ݽ���
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

// ���ݷ���
int Serial::sendData(const char* data, int maxSize)
{
    return write(d->fd, data, maxSize);
}

