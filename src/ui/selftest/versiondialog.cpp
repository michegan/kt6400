#include "versionxml.h"
#include "versiondialog.h"


VersionDialog::VersionDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 加载版本信息
    this->loadVersionInfo();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
}

VersionDialog::~VersionDialog()
{

}

// 界面字符串
void VersionDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbOk, "IDS_OK");
}

// 加载版本信息
void VersionDialog::loadVersionInfo()
{
    VersionXml xml;
    if (xml.load())
    {
        ui.leAppVersion->setText(xml.getTextValue2(KEY1_VERSION, KEY2_APP));
        ui.leKernelVersion->setText(xml.getTextValue2(KEY1_VERSION, KEY2_KERNEL));
        ui.leMcuVersion->setText(xml.getTextValue2(KEY1_VERSION, KEY2_MCU));
        ui.leFpgaVersion->setText(xml.getTextValue2(KEY1_VERSION, KEY2_FPGA));
    }
}