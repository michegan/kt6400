#ifndef _HELP_DIALOG_H_
#define _HELP_DIALOG_H_


#include "dialog.h"

#include "ui_helpdialog.h"


// 模式编辑对话框
class HelpDialog : public Dialog
{
    Q_OBJECT

public:
    HelpDialog(QWidget* parent = 0);
    virtual ~HelpDialog();

private slots:
    // 按钮点击
    void onBtnOkClicked();
    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

private:
    // 界面
    Ui::HelpDialog ui;
};


#endif // _HELP_DIALOG_H_