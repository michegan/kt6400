#include "enum.h"
#include "seqfile.h"
#include "asynctimeseq.h"
#include "maintaindialog.h"


MaintainDialog::MaintainDialog(QWidget* parent)
    : ProgressDialog(parent), timeseq(new AsyncTimeseq())
{
    // 关联信号槽
    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

MaintainDialog::~MaintainDialog()
{
    // 时序执行体
    delete this->timeseq;
}

// 执行时序
void MaintainDialog::runTimeseq(const QString& seqNo)
{
    this->seqNo = seqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // 时序进度
        float time = SeqFile::getSeqTime(seqNo);
        this->exec(time);
    }
}

// 时序结束
void MaintainDialog::onTimeseqFinished(const QString& seqNo, bool result)
{
    // 关闭对话框
    this->accept();
}