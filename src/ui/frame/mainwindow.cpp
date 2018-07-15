#include <QtDebug>
#include <QKeyEvent>

#include "hal.h"
#include "cache.h"
#include "halfpga.h"
#include "menuwin.h"
#include "loginwin.h"
#include "sysstate.h"
#include "mainwindow.h"
#include "halnetlink.h"


#define WINDOW_WIDTH        (800)
#define WINDOW_HEIGHT       (600)


MainWindow::MainWindow(QWidget* parent)
    : QDialog(parent, Qt::FramelessWindowHint), timer(new QTimer()), funcWin(0)
{
    // 主窗口大小
    this->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 菜单功能窗口
    this->onSwitchToFuncWin(new LoginWin());

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    // 启动定时器
    this->timer->start(300);
}

MainWindow::~MainWindow()
{
    // 定时器
    delete this->timer;
}

// 按键响应
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QDialog::keyPressEvent(event);

    // 模拟吸样键
    if ((Qt::AltModifier & event->modifiers()) && (Qt::Key_K == event->key()))
    {
        if (this->isAbsorbKeyEnabled())
        {
            this->funcWin->onAbsorbKeyDown();
        }
    }
}

// 定时器超时
void MainWindow::onTimerOut()
{
    int state = 0;
    if (HalFpga::query(ABSORBKEY_STATE, (char*)&state, sizeof(state)))
    {
        qDebug() << "MainWindow onTimerOut state" << state;

        // 状态监测（1：按下；其他：未按下）
        if (1 == state)
        {
            if (this->isAbsorbKeyEnabled())
            {
                this->funcWin->onAbsorbKeyDown();
            }
            else
            {
                qWarning() << "MainWindow onTimerOut isAbsorbKeyEnabled false";
            }
        }
    }

    // WBC HGB数据采集相关处理
    if (!this->isAbsorbKeyEnabled())
    {
        HalNetlink::recv_whmsg_from_drv();
    }
}

// 切换到功能窗口
void MainWindow::onSwitchToFuncWin(FuncWin* funcWin)
{
    QString wIdTo = "";
    QString wIdFrom = "";

    // 当前功能窗口
    if (this->funcWin)
    {
        // 窗口标识
        wIdFrom = this->funcWin->wId();

        // 和当前主窗口脱离父子关系，为接下来的delete操作做准备
        this->funcWin->setParent(0);

        // 断开窗口切换信号槽
        this->disconnect(funcWin, SIGNAL(toFuncWin(FuncWin*)), this, SLOT(onSwitchToFuncWin(FuncWin*)));

        // 释放当前功能窗口
        delete this->funcWin;
        this->funcWin = 0;
    }

    if (funcWin)
    {
        // 窗口标识
        wIdTo = funcWin->wId();

        // 指定新窗口位置，并显示
        funcWin->setParent(this);
        funcWin->setGeometry(0, 0, this->width(), this->height());
        funcWin->show();

        // 关联窗口切换信号槽
        this->connect(funcWin, SIGNAL(toFuncWin(FuncWin*)), this, SLOT(onSwitchToFuncWin(FuncWin*)), Qt::QueuedConnection);

        // 新功能窗口作为当前功能窗口
        this->funcWin = funcWin;
    }

    qDebug() << "MainWindow onSwitchToFuncWin" << wIdFrom << " -> " << wIdTo;
}

// 是否响应吸样键
bool MainWindow::isAbsorbKeyEnabled() const
{
    const SysState* sysState = Cache::sysState();
    return (sysState && sysState->isAbsorbKeyEnabled());
}