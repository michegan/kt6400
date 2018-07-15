#ifndef _ADD_DILUENT_DIALOG_H_
#define _ADD_DILUENT_DIALOG_H_


#include "dialog.h"
#include "ui_adddiluentdialog.h"

class AsyncTimeseq;


// 加稀释液对话框
class AddDiluentDialog : public Dialog
{
    Q_OBJECT

public:
    AddDiluentDialog(QWidget* parent = 0);
    virtual ~AddDiluentDialog();

    // 吸样键按下
    void onAbsorbKeyDown();

private slots:
    // 定时器超时
    void onTimerOut();
    void onPrepareTimerOut();

    // 按钮点击
    void onBtnAddDiluentClicked();
    void onBtnCancelClicked();

    // 时序结束
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // 使能界面
    void enableWindow(bool enable);

private:
    // 加稀释液次数
    int times;

    // 进度定时器
    QTimer* timer;

    // 时序号（加稀释液准备）
    QString prepareSeqNo;
    // 时序号（加稀释液）
    QString addDiluentSeqNo;
    // 时序号（加稀释液清洗）
    QString cleanningSeqNo;

    // 时序执行体
    AsyncTimeseq* timeseq;

    // 界面
    Ui::AddDiluentDialog ui;
};


#endif // _ADD_DILUENT_DIALOG_H_