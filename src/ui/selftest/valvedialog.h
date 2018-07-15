#ifndef _VAVLE_DIALOG_H_
#define _VAVLE_DIALOG_H_


#include "dialog.h"
#include "ui_valvedialog.h"


// 阀自检界面
class ValveDialog : public Dialog
{
    Q_OBJECT

public:
    ValveDialog(QWidget* parent = 0);
    virtual ~ValveDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

    // 界面使能
    virtual void enableWindow(bool enable);

private slots:
    // 定时器超时
    void onTimerOut();

    // 按钮点击
    void onBtnValve1Clicked();
    void onBtnValve2Clicked();
    void onBtnValve3Clicked();
    void onBtnValve4Clicked();
    void onBtnValve5Clicked();
    void onBtnValve6Clicked();
    void onBtnValve7Clicked();
    void onBtnValve8Clicked();
    void onBtnValve9Clicked();
    void onBtnValve10Clicked();
    void onBtnValve11Clicked();
    void onBtnValve12Clicked();

private:
    // 阀点击
    void onBtnValveClicked(quint8 vno);
    void onBtnValveClicked(quint8 vno, bool open);

private:
    // 阀号
    quint8 vno;

    // 界面
    Ui::ValveDialog ui;
};


#endif // _VAVLE_DIALOG_H_