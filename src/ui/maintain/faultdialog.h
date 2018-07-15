#ifndef _FAULT_DIALOG_H_
#define _FAULT_DIALOG_H_


#include "dialog.h"

#include "ui_faultdialog.h"


// 故障对话框
class FaultDialog : public Dialog
{
    Q_OBJECT

public:
    FaultDialog(QWidget* parent = 0);
    virtual ~FaultDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    void onBtnCancelClicked();
    void onBtnRelieveClicked();

private:
    // 界面
    Ui::FaultDialog ui;
};


#endif // _FAULT_DIALOG_H_