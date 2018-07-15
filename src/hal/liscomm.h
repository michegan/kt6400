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


// LISͨ���߳�
class HAL_EXPORT LisComm : public QThread
{
    Q_OBJECT

public:
    LisComm();
    virtual ~LisComm();

    // ��������
    QString sendQcSample(const SampleInfo& sampleInfo, const ParaList& paraResult);
    QString sendNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits);

signals:
    // ���ݷ�Ŷ�ͽ���
    void sendFinished(const QString& guid, bool result);

protected:
    // �߳�ִ����
    virtual void run();

private:
    // ����һ������
    void sendSample(const QString& guid);

    // ���һ������
    QByteArray packQCSample(const SampleInfo& sampleInfo, const ParaList& paraResult);
    QByteArray packNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits);

private:
    // ��ͨ��������
    QMutex* mutex;

    // ͨ�Ŵ���
    QextSerialPort* serial;

    // ��ͨ������
    QStringList guids;
    QMap<QString, ParaList> lowLimits;
    QMap<QString, ParaList> highLimits;
    QMap<QString, ParaList> paraResults;
    QMap<QString, SampleInfo> sampleInfos;
};


#endif // _LIS_COMM_THREAD_H_
