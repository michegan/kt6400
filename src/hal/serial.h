#ifndef _SERIAL_H_
#define _SERIAL_H_


#include "libhal.h"


class SerialPrivate;


// ����ͨ��
class HAL_EXPORT Serial
{
public:
    Serial();
    virtual ~Serial();

    // ��
    virtual bool open(const QString& name, int baudrate, int databits);

    // �ر�
    virtual void close();
    
    // ���ݽ���
    int readData(char* data, int maxSize);

    // ���ݷ���
    int sendData(const char* data, int maxSize);

private:
    SerialPrivate* d;
};


#endif // _SERIAL_H_