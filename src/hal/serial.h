#ifndef _SERIAL_H_
#define _SERIAL_H_


#include "libhal.h"


class SerialPrivate;


// 串口通信
class HAL_EXPORT Serial
{
public:
    Serial();
    virtual ~Serial();

    // 打开
    virtual bool open(const QString& name, int baudrate, int databits);

    // 关闭
    virtual void close();
    
    // 数据接收
    int readData(char* data, int maxSize);

    // 数据发送
    int sendData(const char* data, int maxSize);

private:
    SerialPrivate* d;
};


#endif // _SERIAL_H_