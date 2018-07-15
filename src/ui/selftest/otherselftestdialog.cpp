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

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
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

// �����ַ���
void OtherSelftestDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbConst, "IDS_CONST");
    this->setText(ui.pbBuzzer, "IDS_BUZZER");
    this->setText(ui.pbHgbLed, "IDS_HGB_LED");
    this->setText(ui.pbWbcBurn, "IDS_WBC_BURN");
    this->setText(ui.pbRbcBurn, "IDS_RBC_BURN");

    this->setText(ui.pbOk, "IDS_OK");
}

// ��ť���
void OtherSelftestDialog::onBtnConstClicked()
{
    this->onBtnClicked(WBC_CONST);
}

void OtherSelftestDialog::onBtnBuzzerClicked()
{
    Timeseq::buzzer(true);

    // ����3��
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

// ��ť���
void OtherSelftestDialog::onBtnClicked(int cmd)
{
    HalFpga::write(cmd, 1);

    // ����3��
    Utility::ssleep(3);

    HalFpga::write(cmd, 0);
}