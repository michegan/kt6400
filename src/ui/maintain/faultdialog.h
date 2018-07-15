#ifndef _FAULT_DIALOG_H_
#define _FAULT_DIALOG_H_


#include "dialog.h"

#include "ui_faultdialog.h"


// ���϶Ի���
class FaultDialog : public Dialog
{
    Q_OBJECT

public:
    FaultDialog(QWidget* parent = 0);
    virtual ~FaultDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    void onBtnCancelClicked();
    void onBtnRelieveClicked();

private:
    // ����
    Ui::FaultDialog ui;
};


#endif // _FAULT_DIALOG_H_