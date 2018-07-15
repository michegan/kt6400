#ifndef _OTHER_SELFTEST_DIALOG_H_
#define _OTHER_SELFTEST_DIALOG_H_


#include "dialog.h"
#include "ui_otherselftestdialog.h"


// 其他自检界面
class OtherSelftestDialog : public Dialog
{
    Q_OBJECT

public:
    OtherSelftestDialog(QWidget* parent = 0);
    virtual ~OtherSelftestDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    void onBtnConstClicked();
    void onBtnBuzzerClicked();
    void onBtnHgbLedClicked();
    void onBtnWbcBurnClicked();
    void onBtnRbcBurnClicked();

private:
    // 按钮点击
    void onBtnClicked(int cmd);

private:
    // 界面
    Ui::OtherSelftestDialog ui;
};


#endif // _OTHER_SELFTEST_DIALOG_H_