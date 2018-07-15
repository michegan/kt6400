#ifndef _USER_SETUP_DIALOG_H_
#define _USER_SETUP_DIALOG_H_


#include "user.h"
#include "dialog.h"
#include "ui_usersetupdialog.h"

class UserTable;
class UserTableWidget;


// 用户设置对话框
class UserSetupDialog : public Dialog
{
    Q_OBJECT

public:
    UserSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~UserSetupDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 数据变化
    void onUserTableDataChanged();

    // 按钮点击
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnDeleteClicked();
    virtual void onBtnCancelClicked();

private:
    // 用户信息
    QList<int> fids;
    QList<User> users;

    // 用户表
    UserTable* userTable;
    // 用户列表
    UserTableWidget* tableWidget;

    // 界面
    Ui::UserSetupDialog ui;
};


#endif // _USER_SETUP_DIALOG_H_