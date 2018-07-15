#include <QtDebug>

#include "path.h"
#include "cache.h"
#include "usertable.h"
#include "messagebox.h"
#include "usereditdialog.h"
#include "usersetupdialog.h"
#include "usertablewidget.h"


UserSetupDialog::UserSetupDialog(QWidget* parent, Qt::WFlags flags)
    : Dialog(parent), userTable(new UserTable()), tableWidget(new UserTableWidget(this))
{
    ui.setupUi(this);

    // 用户列表
    this->tableWidget->setGeometry(20, 20, 420, 460);

    // 加载所有用户信息
    this->onUserTableDataChanged();

    // 关联信号槽
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->userTable, SIGNAL(dataChanged()), this, SLOT(onUserTableDataChanged()));
}

UserSetupDialog::~UserSetupDialog()
{

}

// 界面字符串
void UserSetupDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 数据变化
void UserSetupDialog::onUserTableDataChanged()
{
    // 登录用户
    const User* currentUser = Cache::currentUser();

    // 系统所有用户
    this->fids = this->userTable->users();

    // 满足条件的用户才显示在用户表格中
    this->users.clear();

    foreach (int fid, this->fids)
    {
        User user;
        if (this->userTable->user(fid, user.userName, user.fullName, user.password, user.userLevel))
        {
            if (user.userLevel <= currentUser->userLevel)
            {
                users.append(user);
            }
        }
    }

    // 刷新用户列表
    this->tableWidget->setUsers(this->users);
}

// 按钮点击
void UserSetupDialog::onBtnAddClicked()
{
    UserEditDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        // 新用户
        User user = dialog.getUser();

        // 用户名是否重复
        QList<int> fids = this->userTable->fids(user.userName);
        if (0 < fids.length())
        {
            // 用户名重复，不能新增
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // 保存到数据库
            int fid = 0;
            this->userTable->insertUser(fid, user.userName, user.fullName, user.password, user.userLevel);
        }
    }
}

void UserSetupDialog::onBtnEditClicked()
{
    // 可以编辑当前用户
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        UserEditDialog dialog(this);

        dialog.setUser(this->users[row]);
        if (QDialog::Accepted == dialog.exec())
        {
            // 新用户
            User user = dialog.getUser();

            // 用户名是否重复
            QList<int> fids = this->userTable->fids(user.userName);
            if (1 < fids.length())
            {
                // 用户名重复，不能新增
                MessageBox::warningIds(this, "IDS_USER_EXIST");
            }
            else
            {
                this->userTable->updateUser(this->fids.at(row), user.userName, user.fullName, user.password, user.userLevel);
            }
        }
    }
}

void UserSetupDialog::onBtnDeleteClicked()
{
    // 可以删除当前用户
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        this->userTable->deleteUser(this->fids.at(row));
    }
}

void UserSetupDialog::onBtnCancelClicked()
{
    this->reject();
}