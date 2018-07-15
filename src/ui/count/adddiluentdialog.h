#ifndef _ADD_DILUENT_DIALOG_H_
#define _ADD_DILUENT_DIALOG_H_


#include "dialog.h"
#include "ui_adddiluentdialog.h"

class AsyncTimeseq;


// ��ϡ��Һ�Ի���
class AddDiluentDialog : public Dialog
{
    Q_OBJECT

public:
    AddDiluentDialog(QWidget* parent = 0);
    virtual ~AddDiluentDialog();

    // ����������
    void onAbsorbKeyDown();

private slots:
    // ��ʱ����ʱ
    void onTimerOut();
    void onPrepareTimerOut();

    // ��ť���
    void onBtnAddDiluentClicked();
    void onBtnCancelClicked();

    // ʱ�����
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // ʹ�ܽ���
    void enableWindow(bool enable);

private:
    // ��ϡ��Һ����
    int times;

    // ���ȶ�ʱ��
    QTimer* timer;

    // ʱ��ţ���ϡ��Һ׼����
    QString prepareSeqNo;
    // ʱ��ţ���ϡ��Һ��
    QString addDiluentSeqNo;
    // ʱ��ţ���ϡ��Һ��ϴ��
    QString cleanningSeqNo;

    // ʱ��ִ����
    AsyncTimeseq* timeseq;

    // ����
    Ui::AddDiluentDialog ui;
};


#endif // _ADD_DILUENT_DIALOG_H_