#include "serial.h"


Serial::Serial()
    : d(0)
{

}

Serial::~Serial()
{

}

// ���豸
bool Serial::open(const QString& name, int baudrate, int databits)
{
    return true;
}

// �ر��豸
void Serial::close()
{

}

// ���ݽ���
int Serial::readData(char* data, int maxSize)
{
    return maxSize;
}

// ���ݷ���
int Serial::sendData(const char* data, int maxSize)
{
    return maxSize;
}