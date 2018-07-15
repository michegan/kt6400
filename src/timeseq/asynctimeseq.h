#ifndef _ASYNC_TIMESEQ_H_
#define _ASYNC_TIMESEQ_H_


#include <QTimer>
#include <QObject>

#include "libtimeseq.h"

class Timeseq;
class SysState;


// 时序执行（异步）
class TIMESEQ_EXPORT AsyncTimeseq : public QObject
{
    Q_OBJECT

public:
    AsyncTimeseq();
    virtual ~AsyncTimeseq();

    // 执行时序
    virtual int runTimeseq(const QString& seqNo);

signals:
    // 数据采集结束
    void dmaDataReady();

    // 时序执行结束
    void timeseqFinished(const QString& seqNo, bool result);

private slots:
    // 时序结束
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // 时序执行体
    Timeseq* timeseq;

    // 系统状态
    SysState* sysState;
};


#endif // _ASYNC_TIMESEQ_H_