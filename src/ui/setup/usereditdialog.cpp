#include <QtDebug>

#include "define.h"
#include "messagebox.h"
#include "usereditdialog.h"


UserEditDialog::UserEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 最大长度

    // 最大长度
    ui.leUserName->setMaxLength(MAX_USERNAME_LEN);
    ui.lePassword->setMaxLength(MAX_PASSWORD_LEN);
    ui.lePasswordConfirm->setMaxLength(MAX_PASSWORD_LEN);
    ui.leFullName->setMaxLength(MAX_USERNAME_LEN);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

UserEditDialog::~UserEditDialog()
{

}

// 样本信息
User UserEditDialog::getUser()
{
    User user;

    user.userName = ui.leUserName->text();
    user.password = ui.lePassword->text();
    user.fullName = ui.leFullName->text();
    user.userLevel = ui.cbAdmin->isChecked() ? USER_ADMIN : USER_NORMAL;

    return user;
}

void UserEditDialog::setUser(const User& user)
{
    ui.leUserName->setText(user.userName);
    ui.lePassword->setText(user.password);
    ui.lePasswordConfirm->setText(user.password);
    ui.leFullName->setText(user.fullName);
    ui.cbAdmin->setChecked(USER_ADMIN == user.userLevel);
}

// 界面字符串
void UserEditDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.lbUserName, "IDS_USER_NAME");
    this->setText(ui.lbPassword, "IDS_PASSWORD");
    this->setText(ui.lbPasswordConfirm, "IDS_PASSWORD_CONFIRM");
    this->setText(ui.lbFullName, "IDS_FULL_NAME");
    this->setText(ui.cbAdmin, "IDS_ADMINISTRATOR");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 按钮点击
void UserEditDialog::onBtnOkClicked()
{
    // 获取样本信息
    QString password = ui.lePassword->text();
    QString passwordConfirm = ui.lePasswordConfirm->text();

    if (password != passwordConfirm)
    {
        MessageBox::warningIds(this, "IDS_PASSWORD_UNMATCH");
        return;
    }

    // 关闭对话框
    this->accept();
}

void UserEditDialog::onBtnCancelClicked()
{
    this->reject();
}