#ifndef _LIS_COMM_THREAD_H_
#define _LIS_COMM_THREAD_H_


#include <QMap>
#include <QMap>
#include <QMutex>
#include <QThread>
#include <QByteArray>

#include "para.h"
#include "libhal.h"
#include "sampleinfo.h"


class QextSerialPort;


// LIS通信线程
class HAL_EXPORT LisComm : public QThread
{
    Q_OBJECT

public:
    LisComm();
    virtual ~LisComm();

    // 发送数据
    QString sendQcSample(const SampleInfo& sampleInfo, const ParaList& paraResult);
    QString sendNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits);

signals:
    // 数据发哦送结束
    void sendFinished(const QString& guid, bool result);

protected:
    // 线程执行体
    virtual void run();

private:
    // 发送一个样本
    void sendSample(const QString& guid);

    // 打包一个样本
    QByteArray packQCSample(const SampleInfo& sampleInfo, const ParaList& paraResult);
    QByteArray packNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits);

private:
    // 待通信内容锁
    QMutex* mutex;

    // 通信串口
    QextSerialPort* serial;

    // 待通信内容
    QStringList guids;
    QMap<QString, ParaList> lowLimits;
    QMap<QString, ParaList> highLimits;
    QMap<QString, ParaList> paraResults;
    QMap<QString, SampleInfo> sampleInfos;
};


#endif // _LIS_COMM_THREAD_H_
