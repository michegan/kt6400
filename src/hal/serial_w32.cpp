#include "serial.h"


Serial::Serial()
    : d(0)
{

}

Serial::~Serial()
{

}

// 打开设备
bool Serial::open(const QString& name, int baudrate, int databits)
{
    return true;
}

// 关闭设备
void Serial::close()
{

}

// 数据接收
int Serial::readData(char* data, int maxSize)
{
    return maxSize;
}

// 数据发送
int Serial::sendData(const char* data, int maxSize)
{
    return maxSize;
}