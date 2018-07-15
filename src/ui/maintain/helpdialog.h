#ifndef _HELP_DIALOG_H_
#define _HELP_DIALOG_H_


#include "dialog.h"

#include "ui_helpdialog.h"


// ģʽ�༭�Ի���
class HelpDialog : public Dialog
{
    Q_OBJECT

public:
    HelpDialog(QWidget* parent = 0);
    virtual ~HelpDialog();

private slots:
    // ��ť���
    void onBtnOkClicked();
    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

private:
    // ����
    Ui::HelpDialog ui;
};


#endif // _HELP_DIALOG_H_