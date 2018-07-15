#ifndef _USER_SETUP_DIALOG_H_
#define _USER_SETUP_DIALOG_H_


#include "user.h"
#include "dialog.h"
#include "ui_usersetupdialog.h"

class UserTable;
class UserTableWidget;


// �û����öԻ���
class UserSetupDialog : public Dialog
{
    Q_OBJECT

public:
    UserSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~UserSetupDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ���ݱ仯
    void onUserTableDataChanged();

    // ��ť���
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnDeleteClicked();
    virtual void onBtnCancelClicked();

private:
    // �û���Ϣ
    QList<int> fids;
    QList<User> users;

    // �û���
    UserTable* userTable;
    // �û��б�
    UserTableWidget* tableWidget;

    // ����
    Ui::UserSetupDialog ui;
};


#endif // _USER_SETUP_DIALOG_H_