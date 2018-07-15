#ifndef _MCU_COMM_THREAD_H_
#define _MCU_COMM_THREAD_H_


#include <QMap>
#include <QThread>
#include <QByteArray>
#include <QSemaphore>

#include "libhal.h"

class QextSerialPort;


// MCU通信线程
class HAL_EXPORT McuComm : public QThread
{
    Q_OBJECT

public:
    McuComm();
    virtual ~McuComm();

    // 数据发送
    bool write(const QByteArray& dataArray);
    bool post(const QByteArray& dataArray);
    bool query(const QByteArray& dataArray, char* result);

signals:
    // 数据采集结束
    void dmaDataReady();

    // 故障上报
    void newFault(int fault);

public:
    // 计算校验和
    static char checkSum(const QByteArray& byteArray);

protected:
    // 线程执行体
    virtual void run();

private slots:
    // 串口数据就绪
    void onReadyRead();

private:
    // 收到一个数据包处理
    void onRecvOnePackage(const QByteArray& byteArray);

    // 提取一个数据包
    QByteArray getOnePackage(const QByteArray& byteArray);

private:
    // 接收缓冲区
    QByteArray recvArray;

    // 通信串口
    QextSerialPort* serial;

    // 同步链表
    QMap<int, QSemaphore*> waitSem;
    QMap<int, QByteArray> waitArray;
};


#endif // _MCU_COMM_THREAD_H_
