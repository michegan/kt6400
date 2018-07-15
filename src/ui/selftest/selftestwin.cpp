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

    // 窗口标识
    this->setWId("SelftestWin");

    // 创建状态条
    this->createStatusBar();

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    this->connect(ui.pbMotor, SIGNAL(clicked()), this, SLOT(onBtnMotorClicked()));
    this->connect(ui.pbValve, SIGNAL(clicked()), this, SLOT(onBtnValveClicked()));
    this->connect(ui.pbOther, SIGNAL(clicked()), this, SLOT(onBtnOtherClicked()));
    this->connect(ui.pbSensor, SIGNAL(clicked()), this, SLOT(onBtnSensorClicked()));
    this->connect(ui.pbVersion, SIGNAL(clicked()), this, SLOT(onBtnVersionClicked()));
}

SelftestWin::~SelftestWin()
{

}

// 界面字符串
void SelftestWin::setWindowText()
{
    // 基类处理
    FuncWin::setWindowText();

    // 子类处理
    this->setText(ui.pbMotor, "IDS_MOTOR");
    this->setText(ui.pbValve, "IDS_VALVE");
    this->setText(ui.pbOther, "IDS_OTHER");
    this->setText(ui.pbSensor, "IDS_SENSOR");
    this->setText(ui.pbVersion, "IDS_VERSION");
}

// 按钮点击
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