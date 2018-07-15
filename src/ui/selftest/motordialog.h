#ifndef _MOTOR_DIALOG_H_
#define _MOTOR_DIALOG_H_


#include "dialog.h"
#include "ui_motordialog.h"


// ����Լ����
class MotorDialog : public Dialog
{
    Q_OBJECT

public:
    MotorDialog(QWidget* parent = 0);
    virtual ~MotorDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����ʹ��
    virtual void enableWindow(bool enable);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

    // ��ť���
    void onBtnMotorXClicked();
    void onBtnMotorYClicked();
    void onBtnSyringe1Clicked();
    void onBtnSyringe2Clicked();

private:
    // ������
    void onBtnMotorClicked(quint8 mno);

private:
    // �����
    quint8 mno;

    // ����
    Ui::MotorDialog ui;
};


#endif // _MOTOR_DIALOG_H_