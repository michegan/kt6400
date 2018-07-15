#include "motordialog.h"
#include "selftestwin.h"
#include "valvedialog.h"
#include "sensordialog.h"
#include "versiondialog.h"
#include "otherselftestdialog.h"


SelftestWin::SelftestWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // ���ڱ�ʶ
    this->setWId("SelftestWin");

    // ����״̬��
    this->createStatusBar();

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
    this->connect(ui.pbMotor, SIGNAL(clicked()), this, SLOT(onBtnMotorClicked()));
    this->connect(ui.pbValve, SIGNAL(clicked()), this, SLOT(onBtnValveClicked()));
    this->connect(ui.pbOther, SIGNAL(clicked()), this, SLOT(onBtnOtherClicked()));
    this->connect(ui.pbSensor, SIGNAL(clicked()), this, SLOT(onBtnSensorClicked()));
    this->connect(ui.pbVersion, SIGNAL(clicked()), this, SLOT(onBtnVersionClicked()));
}

SelftestWin::~SelftestWin()
{

}

// �����ַ���
void SelftestWin::setWindowText()
{
    // ���ദ��
    FuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbMotor, "IDS_MOTOR");
    this->setText(ui.pbValve, "IDS_VALVE");
    this->setText(ui.pbOther, "IDS_OTHER");
    this->setText(ui.pbSensor, "IDS_SENSOR");
    this->setText(ui.pbVersion, "IDS_VERSION");
}

// ��ť���
void SelftestWin::onBtnMotorClicked()
{
    MotorDialog dialog(this);
    dialog.exec();
}

void SelftestWin::onBtnValveClicked()
{
    ValveDialog dialog(this);
    dialog.exec();
}

void SelftestWin::onBtnOtherClicked()
{
    OtherSelftestDialog dialog(this);
    dialog.exec();
}

void SelftestWin::onBtnSensorClicked()
{
    SensorDialog dialog(this);
    dialog.exec();
}

void SelftestWin::onBtnVersionClicked()
{
    VersionDialog dialog(this);
    dialog.exec();
}