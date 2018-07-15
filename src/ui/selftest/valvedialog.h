#ifndef _VAVLE_DIALOG_H_
#define _VAVLE_DIALOG_H_


#include "dialog.h"
#include "ui_valvedialog.h"


// ���Լ����
class ValveDialog : public Dialog
{
    Q_OBJECT

public:
    ValveDialog(QWidget* parent = 0);
    virtual ~ValveDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����ʹ��
    virtual void enableWindow(bool enable);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

    // ��ť���
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
    // �����
    void onBtnValveClicked(quint8 vno);
    void onBtnValveClicked(quint8 vno, bool open);

private:
    // ����
    quint8 vno;

    // ����
    Ui::ValveDialog ui;
};


#endif // _VAVLE_DIALOG_H_