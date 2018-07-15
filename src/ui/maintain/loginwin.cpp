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

    // 界面字符串
    this->setWindowText();

    // 窗口标识
    this->setWId("LoginWin");

    // 默认用户名，密码
    ui.leName->setText("Admin");
    ui.lePassword->setText("admin");

    // 最大长度
    ui.leName->setMaxLength(MAX_USERNAME_LEN);
    ui.lePassword->setMaxLength(MAX_PASSWORD_LEN);

    // 关联信号槽
    this->connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
}

LoginWin::~LoginWin()
{

}

// 界面字符串
void LoginWin::setWindowText()
{
    // 基类处理
    // FuncWin::setWindowText();

    // 子类处理
    this->setText(ui.pbOk, "IDS_LOGIN");
    this->setText(ui.lbName, "IDS_NAME");
    this->setText(ui.lbPassword, "IDS_PASSWORD");
}

// 事件处理
void LoginWin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 绘制背景图
    const QImage* image = Resource::image("big_logo");
    if (image)
    {
        painter.drawImage(150, 0, *image);
    }

    // 基类处理
    FuncWin::paintEvent(event);
}

// 按钮点击
void LoginWin::onBtnOkClicked()
{
    QString alert = "";

    do 
    {
        // 用户信息
        QString iUserName = ui.leName->text();
        QString iPassword = ui.lePassword->text();

        // 用户名不能为空
        if (iUserName.isEmpty())
        {
            alert = "IDS_INPUT_USER_NAME";
            break;
        }

        // 完整用户信息
        int userLevel = 0;
        QString fullName = "";

        // 特殊用户
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

            // 判定用户是否存在
            QList<int> fids = userTable.fids(iUserName);
            if (fids.isEmpty())
            {
                alert = "IDS_INVALID_USER_NAME";
                break;
            }

            // 用户存在，读取用户信息
            QString dPassword = "";
            if (!userTable.user(fids.first(), iUserName, fullName, dPassword, userLevel))
            {
                break;
            }

            // 普通用户密码匹配
            if (iPassword != dPassword)
            {
                alert = "IDS_INVALID_PASSWORD";
                break;
            }
        }

        // 记录登录用户信息
        User* user = Cache::currentUser();
        if (user)
        {
            user->fullName = fullName;
            user->userLevel = userLevel;
        }
    } while (0);

    // 登录结果处理
    if (alert.isEmpty())
    {
        // 切换到相应界面
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