#include <QtDebug>

#include "enum.h"
#include "cache.h"
#include "funcwin.h"
#include "menuwin.h"
#include "language.h"
#include "resource.h"
#include "sysstate.h"
#include "messagebox.h"
#include "faultdialog.h"
#include "reagentwidget.h"


FuncWin::FuncWin(QWidget* parent)
    : QWidget(parent), winId(""), lbLogo(0), pbMenu(0), pbFault(0), reagentWidget(0)
{

}

FuncWin::~FuncWin()
{

}

// 窗口标识
QString FuncWin::wId() const
{
    return this->winId;
}

void FuncWin::setWId(const QString& wId)
{
    this->winId = wId;
}

// 吸样键按下
void FuncWin::onAbsorbKeyDown()
{
    qDebug() << "FuncWin onAbsorbKeyDown do nothing";
}

// 界面字符串
void FuncWin::setWindowText()
{
    this->setText(this->pbMenu, "IDS_MENU");
}

// 创建状态条
void FuncWin::createStatusBar()
{
    // 顶部状态栏
    this->lbLogo = new QLabel(this); // LOGO标签
    const QImage* image = Resource::image("small_logo");
    if (image)
    {
        this->lbLogo->setPixmap(QPixmap::fromImage(*image));
    }
    this->lbLogo->setGeometry(0, 0, 60, 40);

    this->pbMenu = new QPushButton(this); // 菜单按钮
    this->pbMenu->setGeometry(700, 0, 100, 40);

    // 底部状态栏
    this->pbFault = new QPushButton(this); // 当前故障
    this->pbFault->setFlat(true);
    this->pbFault->setGeometry(480, 565, 200, 32);

    this->reagentWidget = new ReagentWidget(this); // 试剂状态
    this->reagentWidget->setGeometry(740, 565, 60, 32);

    // 关联信号槽
    this->connect(this->pbMenu, SIGNAL(clicked()), this, SLOT(onBtnMenuClicked()));
    this->connect(this->pbFault, SIGNAL(clicked()), this, SLOT(onBtnFaultClicked()));
    this->connect(this->reagentWidget, SIGNAL(clicked()), this, SLOT(onReagentWidgetClicked()));
}

// 界面使能
void FuncWin::enableWindow(bool enable)
{
    this->pbMenu->setEnabled(enable);
    this->pbFault->setEnabled(enable);
    this->reagentWidget->setEnabled(enable);
}

// 吸样键使能
void FuncWin::enableAbsorbKey(bool enable)
{
    SysState* sysState = Cache::sysState();
    if (sysState)
    {
        sysState->setAbsorbKeyState(enable);
    }
}

// 启动时序失败处理
void FuncWin::onRunTimeseqFail(int ret)
{
    QString text;

    qDebug() << "FuncWin onRunTimeseqFail" << ret;

    if (EXIT_BUSY_LIMITED == ret)
    {
        // 系统忙限制
        text = "IDS_SYSTEM_BUSY";
    }
    else if (EXIT_FAULT_LIMITED == ret)
    {
        // 故障限制
        text = "IDS_FAULT_LIMITED";
    }
    else if (EXIT_FAIL == ret)
    {
        // 其他原因限制
        text = "IDS_RUN_FAIL";
    }

    // 提示用户
    if (!text.isEmpty())
    {
        MessageBox::informationIds(this, text);
    }
}

// 切换到功能窗口
void FuncWin::switchToFuncWin(FuncWin* funcWin)
{
    emit toFuncWin(funcWin);
}

// 按钮点击
void FuncWin::onBtnMenuClicked()
{
    this->switchToFuncWin(new MenuWin());
}

void FuncWin::onBtnFaultClicked()
{
    SysState* sysState = Cache::sysState();
    if (sysState && !sysState->faultList().isEmpty())
    {
        FaultDialog dialog(this);
        dialog.exec();
    }
}

void FuncWin::onReagentWidgetClicked()
{

}

// 故障变化
static int s_faultId = -1;
void FuncWin::onFaultChanged(const QList<int>& faults)
{
    if (faults.isEmpty())
    {
        this->pbFault->setText("");
    }
    else
    {
        s_faultId = faults.first();
        this->pbFault->setText(QString::number(s_faultId));
    }
}

// 界面字符串
QString FuncWin::getString(const QString& ids)
{
    return Language::getString(ids);
}

void FuncWin::setText(QLabel* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}

void FuncWin::setText(QLineEdit* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}

void FuncWin::setText(QAbstractButton* widget, const QString& ids)
{
    QString text = this->getString(ids);
    widget->setText(text);
}