#ifndef _ASYNC_TIMESEQ_H_
#define _ASYNC_TIMESEQ_H_


#include <QTimer>
#include <QObject>

#include "libtimeseq.h"

class Timeseq;
class SysState;


// ʱ��ִ�У��첽��
class TIMESEQ_EXPORT AsyncTimeseq : public QObject
{
    Q_OBJECT

public:
    AsyncTimeseq();
    virtual ~AsyncTimeseq();

    // ִ��ʱ��
    virtual int runTimeseq(const QString& seqNo);

signals:
    // ���ݲɼ�����
    void dmaDataReady();

    // ʱ��ִ�н���
    void timeseqFinished(const QString& seqNo, bool result);

private slots:
    // ʱ�����
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // ʱ��ִ����
    Timeseq* timeseq;

    // ϵͳ״̬
    SysState* sysState;
};


#endif // _ASYNC_TIMESEQ_H_