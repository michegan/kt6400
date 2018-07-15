#include <QPainter>

#include "user.h"
#include "cache.h"
#include "define.h"
#include "menuwin.h"
#include "loginwin.h"
#include "resource.h"
#include "sysstate.h"
#include "usertable.h"
#include "messagebox.h"
#include "startupwin.h"


LoginWin::LoginWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ���ڱ�ʶ
    this->setWId("LoginWin");

    // Ĭ���û���������
    ui.leName->setText("Admin");
    ui.lePassword->setText("admin");

    // ��󳤶�
    ui.leName->setMaxLength(MAX_USERNAME_LEN);
    ui.lePassword->setMaxLength(MAX_PASSWORD_LEN);

    // �����źŲ�
    this->connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
}

LoginWin::~LoginWin()
{

}

// �����ַ���
void LoginWin::setWindowText()
{
    // ���ദ��
    // FuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbOk, "IDS_LOGIN");
    this->setText(ui.lbName, "IDS_NAME");
    this->setText(ui.lbPassword, "IDS_PASSWORD");
}

// �¼�����
void LoginWin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // ���Ʊ���ͼ
    const QImage* image = Resource::image("big_logo");
    if (image)
    {
        painter.drawImage(150, 0, *image);
    }

    // ���ദ��
    FuncWin::paintEvent(event);
}

// ��ť���
void LoginWin::onBtnOkClicked()
{
    QString alert = "";

    do 
    {
        // �û���Ϣ
        QString iUserName = ui.leName->text();
        QString iPassword = ui.lePassword->text();

        // �û�������Ϊ��
        if (iUserName.isEmpty())
        {
            alert = "IDS_INPUT_USER_NAME";
            break;
        }

        // �����û���Ϣ
        int userLevel = 0;
        QString fullName = "";

        // �����û�
        bool special = false;

        QList<User> specialUsers = User::specialUsers();
        foreach (User user, specialUsers)
        {
            if (user.userName == iUserName && user.password == iPassword)
            {
                special = true;

                userLevel = user.userLevel;
                fullName = user.fullName;

                break;
            }
        }

        if (!special)
        {
            UserTable userTable;

            // �ж��û��Ƿ����
            QList<int> fids = userTable.fids(iUserName);
            if (fids.isEmpty())
            {
                alert = "IDS_INVALID_USER_NAME";
                break;
            }

            // �û����ڣ���ȡ�û���Ϣ
            QString dPassword = "";
            if (!userTable.user(fids.first(), iUserName, fullName, dPassword, userLevel))
            {
                break;
            }

            // ��ͨ�û�����ƥ��
            if (iPassword != dPassword)
            {
                alert = "IDS_INVALID_PASSWORD";
                break;
            }
        }

        // ��¼��¼�û���Ϣ
        User* user = Cache::currentUser();
        if (user)
        {
            user->fullName = fullName;
            user->userLevel = userLevel;
        }
    } while (0);

    // ��¼�������
    if (alert.isEmpty())
    {
        // �л�����Ӧ����
        SysState* sysState = Cache::sysState();
        if (sysState && sysState->isStartupFinished())
        {
            this->switchToFuncWin(new MenuWin());
        }
        else
        {
            this->switchToFuncWin(new MenuWin());
        }
    }
    else
    {
        MessageBox::warningIds(this, alert);
    }
}