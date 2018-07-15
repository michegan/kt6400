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
    // �����ڴ�С
    this->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // �˵����ܴ���
    this->onSwitchToFuncWin(new LoginWin());

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    // ������ʱ��
    this->timer->start(300);
}

MainWindow::~MainWindow()
{
    // ��ʱ��
    delete this->timer;
}

// ������Ӧ
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QDialog::keyPressEvent(event);

    // ģ��������
    if ((Qt::AltModifier & event->modifiers()) && (Qt::Key_K == event->key()))
    {
        if (this->isAbsorbKeyEnabled())
        {
            this->funcWin->onAbsorbKeyDown();
        }
    }
}

// ��ʱ����ʱ
void MainWindow::onTimerOut()
{
    int state = 0;
    if (HalFpga::query(ABSORBKEY_STATE, (char*)&state, sizeof(state)))
    {
        qDebug() << "MainWindow onTimerOut state" << state;

        // ״̬��⣨1�����£�������δ���£�
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

    // WBC HGB���ݲɼ���ش���
    if (!this->isAbsorbKeyEnabled())
    {
        HalNetlink::recv_whmsg_from_drv();
    }
}

// �л������ܴ���
void MainWindow::onSwitchToFuncWin(FuncWin* funcWin)
{
    QString wIdTo = "";
    QString wIdFrom = "";

    // ��ǰ���ܴ���
    if (this->funcWin)
    {
        // ���ڱ�ʶ
        wIdFrom = this->funcWin->wId();

        // �͵�ǰ���������븸�ӹ�ϵ��Ϊ��������delete������׼��
        this->funcWin->setParent(0);

        // �Ͽ������л��źŲ�
        this->disconnect(funcWin, SIGNAL(toFuncWin(FuncWin*)), this, SLOT(onSwitchToFuncWin(FuncWin*)));

        // �ͷŵ�ǰ���ܴ���
        delete this->funcWin;
        this->funcWin = 0;
    }

    if (funcWin)
    {
        // ���ڱ�ʶ
        wIdTo = funcWin->wId();

        // ָ���´���λ�ã�����ʾ
        funcWin->setParent(this);
        funcWin->setGeometry(0, 0, this->width(), this->height());
        funcWin->show();

        // ���������л��źŲ�
        this->connect(funcWin, SIGNAL(toFuncWin(FuncWin*)), this, SLOT(onSwitchToFuncWin(FuncWin*)), Qt::QueuedConnection);

        // �¹��ܴ�����Ϊ��ǰ���ܴ���
        this->funcWin = funcWin;
    }

    qDebug() << "MainWindow onSwitchToFuncWin" << wIdFrom << " -> " << wIdTo;
}

// �Ƿ���Ӧ������
bool MainWindow::isAbsorbKeyEnabled() const
{
    const SysState* sysState = Cache::sysState();
    return (sysState && sysState->isAbsorbKeyEnabled());
}