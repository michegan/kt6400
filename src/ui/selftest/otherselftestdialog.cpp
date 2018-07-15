#include <QTimer>

#include "hal.h"
#include "halfpga.h"
#include "utility.h"
#include "timeseq.h"
#include "otherselftestdialog.h"


OtherSelftestDialog::OtherSelftestDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));

    connect(ui.pbConst, SIGNAL(clicked()), this, SLOT(onBtnConstClicked()));
    connect(ui.pbBuzzer, SIGNAL(clicked()), this, SLOT(onBtnBuzzerClicked()));
    connect(ui.pbHgbLed, SIGNAL(clicked()), this, SLOT(onBtnHgbLedClicked()));
    connect(ui.pbWbcBurn, SIGNAL(clicked()), this, SLOT(onBtnWbcBurnClicked()));
    connect(ui.pbRbcBurn, SIGNAL(clicked()), this, SLOT(onBtnRbcBurnClicked()));
}

OtherSelftestDialog::~OtherSelftestDialog()
{

}

// 界面字符串
void OtherSelftestDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbConst, "IDS_CONST");
    this->setText(ui.pbBuzzer, "IDS_BUZZER");
    this->setText(ui.pbHgbLed, "IDS_HGB_LED");
    this->setText(ui.pbWbcBurn, "IDS_WBC_BURN");
    this->setText(ui.pbRbcBurn, "IDS_RBC_BURN");

    this->setText(ui.pbOk, "IDS_OK");
}

// 按钮点击
void OtherSelftestDialog::onBtnConstClicked()
{
    this->onBtnClicked(WBC_CONST);
}

void OtherSelftestDialog::onBtnBuzzerClicked()
{
    Timeseq::buzzer(true);

    // 持续3秒
    Utility::ssleep(3);

    Timeseq::buzzer(false);
}

void OtherSelftestDialog::onBtnHgbLedClicked()
{
    this->onBtnClicked(HGB_LED);
}

void OtherSelftestDialog::onBtnWbcBurnClicked()
{
    this->onBtnClicked(WBC_BURN);
}

void OtherSelftestDialog::onBtnRbcBurnClicked()
{
    this->onBtnClicked(RBC_BURN);
}

// 按钮点击
void OtherSelftestDialog::onBtnClicked(int cmd)
{
    HalFpga::write(cmd, 1);

    // 持续3秒
    Utility::ssleep(3);

    HalFpga::write(cmd, 0);
}