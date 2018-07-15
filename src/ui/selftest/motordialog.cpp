#include <QTimer>
#include <QtDebug>

#include "timeseq.h"
#include "motordialog.h"


MotorDialog::MotorDialog(QWidget* parent)
    : Dialog(parent), mno(0)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));

    connect(ui.pbMotorX, SIGNAL(clicked()), this, SLOT(onBtnMotorXClicked()));
    connect(ui.pbMotorY, SIGNAL(clicked()), this, SLOT(onBtnMotorYClicked()));
    connect(ui.pbSyringe1, SIGNAL(clicked()), this, SLOT(onBtnSyringe1Clicked()));
    connect(ui.pbSyringe2, SIGNAL(clicked()), this, SLOT(onBtnSyringe2Clicked()));
}

MotorDialog::~MotorDialog()
{

}

// 界面字符串
void MotorDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.lbResult, "IDS_RESULT");
    this->setText(ui.pbMotorX, "IDS_MOTOR_X");
    this->setText(ui.pbMotorY, "IDS_MOTOR_Y");
    this->setText(ui.pbSyringe1, "IDS_SYRINGE_1");
    this->setText(ui.pbSyringe2, "IDS_SYRINGE_2");
    this->setText(ui.pbOk, "IDS_OK");
}

// 定时器超时
void MotorDialog::onTimerOut()
{
    // 电机初始化（同步接口，界面会阻塞）
    bool ret = false;
    
    // 电机初始化
    if (1 == this->mno)
    {
        ret = Timeseq::motorHInit();
    }
    else if (2 == this->mno)
    {
        ret = Timeseq::motorVInit();
    }
    else if (3 == this->mno)
    {
        ret = Timeseq::motorSpInit();
    }
    else if (4 == this->mno)
    {
        ret = Timeseq::motorVpInit();
    }
    qDebug() << "MotorDialog onTimerOut motorInit" << ret;

    // 显示自检结果
    this->setText(ui.leResult, (ret ? "IDS_SUCCESS" : "IDS_FAIL"));

    // 窗口使能
    this->enableWindow(true);
}

// 按钮点击
void MotorDialog::onBtnMotorXClicked()
{
    this->onBtnMotorClicked(1);
}

void MotorDialog::onBtnMotorYClicked()
{
    this->onBtnMotorClicked(2);
}

void MotorDialog::onBtnSyringe1Clicked()
{
    this->onBtnMotorClicked(3);
}

void MotorDialog::onBtnSyringe2Clicked()
{
    this->onBtnMotorClicked(4);
}

// 窗口使能
void MotorDialog::enableWindow(bool enable)
{
    ui.pbOk->setEnabled(enable);
    ui.pbMotorX->setEnabled(enable);
    ui.pbMotorY->setEnabled(enable);
    ui.pbSyringe1->setEnabled(enable);
    ui.pbSyringe2->setEnabled(enable);
}

// 电机点击
void MotorDialog::onBtnMotorClicked(quint8 mno)
{
    qDebug() << "MotorDialog onBtnMotorClicked" << mno;

    // 电机号
    this->mno = mno;

    // 窗口使能
    this->enableWindow(false);

    // 显示自检结果
    this->setText(ui.leResult, "IDS_SELFTESTING");

    // 启动1秒定时器，定时器到达后执行电机初始化
    QTimer::singleShot(200, this, SLOT(onTimerOut()));
}