#ifndef _MAINTAIN_DIALOG_H_
#define _MAINTAIN_DIALOG_H_


#include "progressdialog.h"

class AsyncTimeseq;


// �ֶ�ά���Ի���
class MaintainDialog : public ProgressDialog
{
    Q_OBJECT

public:
    MaintainDialog(QWidget* parent = 0);
    virtual ~MaintainDialog();

    // ִ��ʱ��
    void runTimeseq(const QString& seqNo);

private slots:
    // ʱ�����
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // ʱ���
    QString seqNo;

    // ʱ��ִ����
    AsyncTimeseq* timeseq;
};


#endif // _MAINTAIN_DIALOG_H_