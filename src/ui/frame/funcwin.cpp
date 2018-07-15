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

// ���ڱ�ʶ
QString FuncWin::wId() const
{
    return this->winId;
}

void FuncWin::setWId(const QString& wId)
{
    this->winId = wId;
}

// ����������
void FuncWin::onAbsorbKeyDown()
{
    qDebug() << "FuncWin onAbsorbKeyDown do nothing";
}

// �����ַ���
void FuncWin::setWindowText()
{
    this->setText(this->pbMenu, "IDS_MENU");
}

// ����״̬��
void FuncWin::createStatusBar()
{
    // ����״̬��
    this->lbLogo = new QLabel(this); // LOGO��ǩ
    const QImage* image = Resource::image("small_logo");
    if (image)
    {
        this->lbLogo->setPixmap(QPixmap::fromImage(*image));
    }
    this->lbLogo->setGeometry(0, 0, 60, 40);

    this->pbMenu = new QPushButton(this); // �˵���ť
    this->pbMenu->setGeometry(700, 0, 100, 40);

    // �ײ�״̬��
    this->pbFault = new QPushButton(this); // ��ǰ����
    this->pbFault->setFlat(true);
    this->pbFault->setGeometry(480, 565, 200, 32);

    this->reagentWidget = new ReagentWidget(this); // �Լ�״̬
    this->reagentWidget->setGeometry(740, 565, 60, 32);

    // �����źŲ�
    this->connect(this->pbMenu, SIGNAL(clicked()), this, SLOT(onBtnMenuClicked()));
    this->connect(this->pbFault, SIGNAL(clicked()), this, SLOT(onBtnFaultClicked()));
    this->connect(this->reagentWidget, SIGNAL(clicked()), this, SLOT(onReagentWidgetClicked()));
}

// ����ʹ��
void FuncWin::enableWindow(bool enable)
{
    this->pbMenu->setEnabled(enable);
    this->pbFault->setEnabled(enable);
    this->reagentWidget->setEnabled(enable);
}

// ������ʹ��
void FuncWin::enableAbsorbKey(bool enable)
{
    SysState* sysState = Cache::sysState();
    if (sysState)
    {
        sysState->setAbsorbKeyState(enable);
    }
}

// ����ʱ��ʧ�ܴ���
void FuncWin::onRunTimeseqFail(int ret)
{
    QString text;

    qDebug() << "FuncWin onRunTimeseqFail" << ret;

    if (EXIT_BUSY_LIMITED == ret)
    {
        // ϵͳæ����
        text = "IDS_SYSTEM_BUSY";
    }
    else if (EXIT_FAULT_LIMITED == ret)
    {
        // ��������
        text = "IDS_FAULT_LIMITED";
    }
    else if (EXIT_FAIL == ret)
    {
        // ����ԭ������
        text = "IDS_RUN_FAIL";
    }

    // ��ʾ�û�
    if (!text.isEmpty())
    {
        MessageBox::informationIds(this, text);
    }
}

// �л������ܴ���
void FuncWin::switchToFuncWin(FuncWin* funcWin)
{
    emit toFuncWin(funcWin);
}

// ��ť���
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

// ���ϱ仯
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

// �����ַ���
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