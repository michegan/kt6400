#include "enum.h"
#include "seqfile.h"
#include "asynctimeseq.h"
#include "maintaindialog.h"


MaintainDialog::MaintainDialog(QWidget* parent)
    : ProgressDialog(parent), timeseq(new AsyncTimeseq())
{
    // �����źŲ�
    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

MaintainDialog::~MaintainDialog()
{
    // ʱ��ִ����
    delete this->timeseq;
}

// ִ��ʱ��
void MaintainDialog::runTimeseq(const QString& seqNo)
{
    this->seqNo = seqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // ʱ�����
        float time = SeqFile::getSeqTime(seqNo);
        this->exec(time);
    }
}

// ʱ�����
void MaintainDialog::onTimeseqFinished(const QString& seqNo, bool result)
{
    // �رնԻ���
    this->accept();
}