#ifndef _MOTOR_DIALOG_H_
#define _MOTOR_DIALOG_H_


#include "dialog.h"
#include "ui_motordialog.h"


// 电机自检界面
class MotorDialog : public Dialog
{
    Q_OBJECT

public:
    MotorDialog(QWidget* parent = 0);
    virtual ~MotorDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

    // 界面使能
    virtual void enableWindow(bool enable);

private slots:
    // 定时器超时
    void onTimerOut();

    // 按钮点击
    void onBtnMotorXClicked();
    void onBtnMotorYClicked();
    void onBtnSyringe1Clicked();
    void onBtnSyringe2Clicked();

private:
    // 电机点击
    void onBtnMotorClicked(quint8 mno);

private:
    // 电机号
    quint8 mno;

    // 界面
    Ui::MotorDialog ui;
};


#endif // _MOTOR_DIALOG_H_