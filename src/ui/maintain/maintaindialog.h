#ifndef _MAINTAIN_DIALOG_H_
#define _MAINTAIN_DIALOG_H_


#include "progressdialog.h"

class AsyncTimeseq;


// 手动维护对话框
class MaintainDialog : public ProgressDialog
{
    Q_OBJECT

public:
    MaintainDialog(QWidget* parent = 0);
    virtual ~MaintainDialog();

    // 执行时序
    void runTimeseq(const QString& seqNo);

private slots:
    // 时序结束
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // 时序号
    QString seqNo;

    // 时序执行体
    AsyncTimeseq* timeseq;
};


#endif // _MAINTAIN_DIALOG_H_