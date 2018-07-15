#include "setupwin.h"
#include "gainsetupdialog.h"
#include "usersetupdialog.h"
#include "printsetupdialog.h"
#include "doctorsetupdialog.h"
#include "machinesetupdialog.h"
#include "datetimesetupdialog.h"
#include "paraunitsetupdialog.h"
#include "refrangesetupdialog.h"
#include "calfactorsetupdialog.h"
#include "departmentsetupdialog.h"


SetupWin::SetupWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // 窗口标识
    this->setWId("SetupWin");

    // 创建状态条
    this->createStatusBar();

    // 界面字符串
    this->setWindowText();

    // 屏蔽部分功能
    ui.pbParaUnit->setVisible(false);

    // 关联信号槽
    this->connect(ui.pbGain, SIGNAL(clicked()), this, SLOT(onBtnGainClicked()));
    this->connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    this->connect(ui.pbDoctor, SIGNAL(clicked()), this, SLOT(onBtnDoctorClicked()));
    this->connect(ui.pbOperator, SIGNAL(clicked()), this, SLOT(onBtnUserClicked()));
    this->connect(ui.pbMachine, SIGNAL(clicked()), this, SLOT(onBtnMachineClicked()));
    this->connect(ui.pbDateTime, SIGNAL(clicked()), this, SLOT(onBtnDateTimeClicked()));
    this->connect(ui.pbParaUnit, SIGNAL(clicked()), this, SLOT(onBtnParaUnitClicked()));
    this->connect(ui.pbRefRange, SIGNAL(clicked()), this, SLOT(onBtnRefRangeClicked()));
    this->connect(ui.pbCalFactor, SIGNAL(clicked()), this, SLOT(onBtnCalFactorClicked()));
    this->connect(ui.pbDepartment, SIGNAL(clicked()), this, SLOT(onBtnDepartmentClicked()));
}

SetupWin::~SetupWin()
{

}

// 界面字符串
void SetupWin::setWindowText()
{
    // 基类处理
    FuncWin::setWindowText();

    // 子类处理
    this->setText(ui.pbGain, "IDS_GAIN");
    this->setText(ui.pbPrint, "IDS_PRINT");
    this->setText(ui.pbMachine, "IDS_MACHINE");
    this->setText(ui.pbDateTime, "IDS_DATE_TIME");
    this->setText(ui.pbParaUnit, "IDS_PARA_UNIT");
    this->setText(ui.pbRefRange, "IDS_REF_RANGE");
    this->setText(ui.pbCalFactor, "IDS_CAL_FACTOR");
}

// 按钮点击
void SetupWin::onBtnGainClicked()
{
    GainSetupDialog* dialog = new GainSetupDialog(this);
    dialog->show();
}

void SetupWin::onBtnUserClicked()
{
    UserSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnPrintClicked()
{
    PrintSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnDoctorClicked()
{
    DoctorSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnMachineClicked()
{
    MachineSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnDateTimeClicked()
{
    DateTimeSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnParaUnitClicked()
{
    ParaUnitSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnRefRangeClicked()
{
    RefRangeSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnCalFactorClicked()
{
    CalFactorSetupDialog dialog(this);
    dialog.exec();
}

void SetupWin::onBtnDepartmentClicked()
{
    DepartmentSetupDialog dialog(this);
    dialog.exec();
}