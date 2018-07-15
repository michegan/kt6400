#include <QtDebug>

#include "enum.h"
#include "cache.h"
#include "timeseq.h"
#include "sysstate.h"
#include "asynctimeseq.h"


AsyncTimeseq::AsyncTimeseq()
    : QObject(), timeseq(new Timeseq()), sysState(Cache::sysState())
{
    // �����źŲ�
    connect(this->timeseq, SIGNAL(dmaDataReady()), this, SIGNAL(dmaDataReady()));
    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

AsyncTimeseq::~AsyncTimeseq()
{
    // ʱ��ִ����
    if (this->timeseq)
    {
        delete this->timeseq;
    }
}

// ִ��ʱ��
int AsyncTimeseq::runTimeseq(const QString& seqNo)
{
    int ret = EXIT_FAIL;

    do 
    {
        // ʱ���
        if (seqNo.isEmpty())
        {
            break;
        }

        // ϵͳ״̬
        if (this->sysState && !this->sysState->isIdle())
        {
            ret = EXIT_BUSY_LIMITED;
            break;
        }

        // ��������
        if (false)
        {
            ret = EXIT_FAULT_LIMITED;
            break;
        }

        // �·�ʱ���
        if (!this->timeseq->runTimeseq(seqNo))
        {
            break;
        }

        // ����ϵͳ״̬
        this->sysState->setRunState(SysState::StateRunning);

        ret = EXIT_OK;
    } while (0);

    return ret;
}

// ʱ�����
void AsyncTimeseq::onTimeseqFinished(const QString& seqNo, bool result)
{
    qDebug() << "AsyncTimeseq onTimeseqFinished" << seqNo << result;

    // ����ϵͳ״̬
    this->sysState->setRunState(SysState::StateReady);

    // �ϱ�ʱ������ź�
    emit timeseqFinished(seqNo, result);
}