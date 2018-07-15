#ifndef _USER_EDIT_DIALOG_H_
#define _USER_EDIT_DIALOG_H_


#include "user.h"
#include "dialog.h"
#include "ui_usereditdialog.h"


// 用户编辑对话框
class UserEditDialog : public Dialog
{
    Q_OBJECT

public:
    UserEditDialog(QWidget* parent = 0);
    virtual ~UserEditDialog();

    // 用户信息
    User getUser();
    void setUser(const User& user);

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 界面
    Ui::UserEditDialog ui;
};


#endif // _USER_EDIT_DIALOG_H_