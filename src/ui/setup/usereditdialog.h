#ifndef _USER_EDIT_DIALOG_H_
#define _USER_EDIT_DIALOG_H_


#include "user.h"
#include "dialog.h"
#include "ui_usereditdialog.h"


// �û��༭�Ի���
class UserEditDialog : public Dialog
{
    Q_OBJECT

public:
    UserEditDialog(QWidget* parent = 0);
    virtual ~UserEditDialog();

    // �û���Ϣ
    User getUser();
    void setUser(const User& user);

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ����
    Ui::UserEditDialog ui;
};


#endif // _USER_EDIT_DIALOG_H_