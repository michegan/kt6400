#include <QTimer>
#include <QtDebug>

#include "timeseq.h"
#include "valvedialog.h"


ValveDialog::ValveDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));

    connect(ui.pbValve1, SIGNAL(clicked()), this, SLOT(onBtnValve1Clicked()));
    connect(ui.pbValve2, SIGNAL(clicked()), this, SLOT(onBtnValve2Clicked()));
    connect(ui.pbValve3, SIGNAL(clicked()), this, SLOT(onBtnValve3Clicked()));
    connect(ui.pbValve4, SIGNAL(clicked()), this, SLOT(onBtnValve4Clicked()));
    connect(ui.pbValve5, SIGNAL(clicked()), this, SLOT(onBtnValve5Clicked()));
    connect(ui.pbValve6, SIGNAL(clicked()), this, SLOT(onBtnValve6Clicked()));
    connect(ui.pbValve7, SIGNAL(clicked()), this, SLOT(onBtnValve7Clicked()));
    connect(ui.pbValve8, SIGNAL(clicked()), this, SLOT(onBtnValve8Clicked()));
    connect(ui.pbValve9, SIGNAL(clicked()), this, SLOT(onBtnValve9Clicked()));
    connect(ui.pbValve10, SIGNAL(clicked()), this, SLOT(onBtnValve10Clicked()));
    connect(ui.pbValve11, SIGNAL(clicked()), this, SLOT(onBtnValve11Clicked()));
    connect(ui.pbValve12, SIGNAL(clicked()), this, SLOT(onBtnValve12Clicked()));
}

ValveDialog::~ValveDialog()
{

}

// 界面字符串
void ValveDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbOk, "IDS_OK");
}

// 窗口使能
void ValveDialog::enableWindow(bool enable)
{
    QList<QPushButton*> buttons;
    buttons << ui.pbOk << ui.pbValve1 << ui.pbValve2 << ui.pbValve3 << ui.pbValve4 << ui.pbValve5 << ui.pbValve6
            << ui.pbValve7 << ui.pbValve8 << ui.pbValve9 << ui.pbValve10 << ui.pbValve11 << ui.pbValve12
            << ui.pbValve13 << ui.pbValve14 << ui.pbValve15 << ui.pbValve16;

    foreach (QPushButton* button, buttons)
    {
        button->setEnabled(enable);
    }
}

// 定时器超时
void ValveDialog::onTimerOut()
{
    // 阀关闭
    this->onBtnValveClicked(this->vno, false);
}

// 按钮点击
void ValveDialog::onBtnValve1Clicked()
{
    this->onBtnValveClicked(1);
}

void ValveDialog::onBtnValve2Clicked()
{
    this->onBtnValveClicked(2);
}

void ValveDialog::onBtnValve3Clicked()
{
    this->onBtnValveClicked(3);
}

void ValveDialog::onBtnValve4Clicked()
{
    this->onBtnValveClicked(4);
}

void ValveDialog::onBtnValve5Clicked()
{
    this->onBtnValveClicked(5);
}

void ValveDialog::onBtnValve6Clicked()
{
    this->onBtnValveClicked(6);
}

void ValveDialog::onBtnValve7Clicked()
{
    this->onBtnValveClicked(7);
}

void ValveDialog::onBtnValve8Clicked()
{
    this->onBtnValveClicked(8);
}

void ValveDialog::onBtnValve9Clicked()
{
    this->onBtnValveClicked(9);
}

void ValveDialog::onBtnValve10Clicked()
{
    this->onBtnValveClicked(10);
}

void ValveDialog::onBtnValve11Clicked()
{
    this->onBtnValveClicked(11);
}

void ValveDialog::onBtnValve12Clicked()
{
    this->onBtnValveClicked(12);
}

// 阀点击
void ValveDialog::onBtnValveClicked(quint8 vno)
{
    // 记录阀号
    this->vno = vno;

    // 阀打开
    this->onBtnValveClicked(vno, true);

    // 启动1秒定时器，定时器到达后关闭阀
    QTimer::singleShot(1000, this, SLOT(onTimerOut()));
}

void ValveDialog::onBtnValveClicked(quint8 vno, bool open)
{
    qDebug() << "ValveDialog onBtnValveClicked" << vno << open;

    // 阀打开/关闭
    Timeseq::valve(vno, open);

    // 界面按钮使能/禁用
    this->enableWindow(!open);
}