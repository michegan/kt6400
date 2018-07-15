#include <QtDebug>

#include "enum.h"
#include "cache.h"
#include "timeseq.h"
#include "sysstate.h"
#include "asynctimeseq.h"


AsyncTimeseq::AsyncTimeseq()
    : QObject(), timeseq(new Timeseq()), sysState(Cache::sysState())
{
    // 关联信号槽
    connect(this->timeseq, SIGNAL(dmaDataReady()), this, SIGNAL(dmaDataReady()));
    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

AsyncTimeseq::~AsyncTimeseq()
{
    // 时序执行体
    if (this->timeseq)
    {
        delete this->timeseq;
    }
}

// 执行时序
int AsyncTimeseq::runTimeseq(const QString& seqNo)
{
    int ret = EXIT_FAIL;

    do 
    {
        // 时序号
        if (seqNo.isEmpty())
        {
            break;
        }

        // 系统状态
        if (this->sysState && !this->sysState->isIdle())
        {
            ret = EXIT_BUSY_LIMITED;
            break;
        }

        // 故障限制
        if (false)
        {
            ret = EXIT_FAULT_LIMITED;
            break;
        }

        // 下发时序包
        if (!this->timeseq->runTimeseq(seqNo))
        {
            break;
        }

        // 更新系统状态
        this->sysState->setRunState(SysState::StateRunning);

        ret = EXIT_OK;
    } while (0);

    return ret;
}

// 时序结束
void AsyncTimeseq::onTimeseqFinished(const QString& seqNo, bool result)
{
    qDebug() << "AsyncTimeseq onTimeseqFinished" << seqNo << result;

    // 更新系统状态
    this->sysState->setRunState(SysState::StateReady);

    // 上报时序结束信号
    emit timeseqFinished(seqNo, result);
}