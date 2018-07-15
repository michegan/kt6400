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

    // �û��б�
    this->tableWidget->setGeometry(20, 20, 420, 460);

    // ���������û���Ϣ
    this->onUserTableDataChanged();

    // �����źŲ�
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->userTable, SIGNAL(dataChanged()), this, SLOT(onUserTableDataChanged()));
}

UserSetupDialog::~UserSetupDialog()
{

}

// �����ַ���
void UserSetupDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ���ݱ仯
void UserSetupDialog::onUserTableDataChanged()
{
    // ��¼�û�
    const User* currentUser = Cache::currentUser();

    // ϵͳ�����û�
    this->fids = this->userTable->users();

    // �����������û�����ʾ���û������
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

    // ˢ���û��б�
    this->tableWidget->setUsers(this->users);
}

// ��ť���
void UserSetupDialog::onBtnAddClicked()
{
    UserEditDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        // ���û�
        User user = dialog.getUser();

        // �û����Ƿ��ظ�
        QList<int> fids = this->userTable->fids(user.userName);
        if (0 < fids.length())
        {
            // �û����ظ�����������
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // ���浽���ݿ�
            int fid = 0;
            this->userTable->insertUser(fid, user.userName, user.fullName, user.password, user.userLevel);
        }
    }
}

void UserSetupDialog::onBtnEditClicked()
{
    // ���Ա༭��ǰ�û�
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        UserEditDialog dialog(this);

        dialog.setUser(this->users[row]);
        if (QDialog::Accepted == dialog.exec())
        {
            // ���û�
            User user = dialog.getUser();

            // �û����Ƿ��ظ�
            QList<int> fids = this->userTable->fids(user.userName);
            if (1 < fids.length())
            {
                // �û����ظ�����������
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
    // ����ɾ����ǰ�û�
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