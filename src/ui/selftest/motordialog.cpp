#include <QTimer>
#include <QtDebug>

#include "timeseq.h"
#include "motordialog.h"


MotorDialog::MotorDialog(QWidget* parent)
    : Dialog(parent), mno(0)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));

    connect(ui.pbMotorX, SIGNAL(clicked()), this, SLOT(onBtnMotorXClicked()));
    connect(ui.pbMotorY, SIGNAL(clicked()), this, SLOT(onBtnMotorYClicked()));
    connect(ui.pbSyringe1, SIGNAL(clicked()), this, SLOT(onBtnSyringe1Clicked()));
    connect(ui.pbSyringe2, SIGNAL(clicked()), this, SLOT(onBtnSyringe2Clicked()));
}

MotorDialog::~MotorDialog()
{

}

// �����ַ���
void MotorDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.lbResult, "IDS_RESULT");
    this->setText(ui.pbMotorX, "IDS_MOTOR_X");
    this->setText(ui.pbMotorY, "IDS_MOTOR_Y");
    this->setText(ui.pbSyringe1, "IDS_SYRINGE_1");
    this->setText(ui.pbSyringe2, "IDS_SYRINGE_2");
    this->setText(ui.pbOk, "IDS_OK");
}

// ��ʱ����ʱ
void MotorDialog::onTimerOut()
{
    // �����ʼ����ͬ���ӿڣ������������
    bool ret = false;
    
    // �����ʼ��
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

    // ��ʾ�Լ���
    this->setText(ui.leResult, (ret ? "IDS_SUCCESS" : "IDS_FAIL"));

    // ����ʹ��
    this->enableWindow(true);
}

// ��ť���
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

// ����ʹ��
void MotorDialog::enableWindow(bool enable)
{
    ui.pbOk->setEnabled(enable);
    ui.pbMotorX->setEnabled(enable);
    ui.pbMotorY->setEnabled(enable);
    ui.pbSyringe1->setEnabled(enable);
    ui.pbSyringe2->setEnabled(enable);
}

// ������
void MotorDialog::onBtnMotorClicked(quint8 mno)
{
    qDebug() << "MotorDialog onBtnMotorClicked" << mno;

    // �����
    this->mno = mno;

    // ����ʹ��
    this->enableWindow(false);

    // ��ʾ�Լ���
    this->setText(ui.leResult, "IDS_SELFTESTING");

    // ����1�붨ʱ������ʱ�������ִ�е����ʼ��
    QTimer::singleShot(200, this, SLOT(onTimerOut()));
}