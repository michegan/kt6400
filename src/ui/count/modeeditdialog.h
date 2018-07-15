#ifndef _MODE_EDIT_DIALOG_H_
#define _MODE_EDIT_DIALOG_H_


#include "modes.h"
#include "dialog.h"
#include "ui_modeeditdialog.h"


// 模式编辑对话框
class ModeEditDialog : public Dialog
{
    Q_OBJECT

public:
    ModeEditDialog(QWidget* parent = 0);
    virtual ~ModeEditDialog();

    // 模式
    Modes getModes() const;
    void setModes(const Modes& modes);

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 模式
    Modes modes;

    // 界面
    Ui::ModeEditDialog ui;
};


#endif // _MODE_EDIT_DIALOG_H_