#ifndef _OTHER_SELFTEST_DIALOG_H_
#define _OTHER_SELFTEST_DIALOG_H_


#include "dialog.h"
#include "ui_otherselftestdialog.h"


// �����Լ����
class OtherSelftestDialog : public Dialog
{
    Q_OBJECT

public:
    OtherSelftestDialog(QWidget* parent = 0);
    virtual ~OtherSelftestDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    void onBtnConstClicked();
    void onBtnBuzzerClicked();
    void onBtnHgbLedClicked();
    void onBtnWbcBurnClicked();
    void onBtnRbcBurnClicked();

private:
    // ��ť���
    void onBtnClicked(int cmd);

private:
    // ����
    Ui::OtherSelftestDialog ui;
};


#endif // _OTHER_SELFTEST_DIALOG_H_