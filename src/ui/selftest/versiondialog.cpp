#include "versionxml.h"
#include "versiondialog.h"


VersionDialog::VersionDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ���ذ汾��Ϣ
    this->loadVersionInfo();

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
}

VersionDialog::~VersionDialog()
{

}

// �����ַ���
void VersionDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbOk, "IDS_OK");
}

// ���ذ汾��Ϣ
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