#ifndef _MCU_COMM_THREAD_H_
#define _MCU_COMM_THREAD_H_


#include <QMap>
#include <QThread>
#include <QByteArray>
#include <QSemaphore>

#include "libhal.h"

class QextSerialPort;


// MCUͨ���߳�
class HAL_EXPORT McuComm : public QThread
{
    Q_OBJECT

public:
    McuComm();
    virtual ~McuComm();

    // ���ݷ���
    bool write(const QByteArray& dataArray);
    bool post(const QByteArray& dataArray);
    bool query(const QByteArray& dataArray, char* result);

signals:
    // ���ݲɼ�����
    void dmaDataReady();

    // �����ϱ�
    void newFault(int fault);

public:
    // ����У���
    static char checkSum(const QByteArray& byteArray);

protected:
    // �߳�ִ����
    virtual void run();

private slots:
    // �������ݾ���
    void onReadyRead();

private:
    // �յ�һ�����ݰ�����
    void onRecvOnePackage(const QByteArray& byteArray);

    // ��ȡһ�����ݰ�
    QByteArray getOnePackage(const QByteArray& byteArray);

private:
    // ���ջ�����
    QByteArray recvArray;

    // ͨ�Ŵ���
    QextSerialPort* serial;

    // ͬ������
    QMap<int, QSemaphore*> waitSem;
    QMap<int, QByteArray> waitArray;
};


#endif // _MCU_COMM_THREAD_H_
