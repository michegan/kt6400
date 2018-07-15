#include "cache.h"
#include "faultid.h"
#include "faultdialog.h"


FaultDialog::FaultDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
    connect(ui.pbRelieve, SIGNAL(clicked()), this, SLOT(onBtnRelieveClicked()));
}

FaultDialog::~FaultDialog()
{

}

// �����ַ���
void FaultDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbRelieve, "IDS_RELIEVE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ��ť���
void FaultDialog::onBtnCancelClicked()
{
    this->reject();
}

void FaultDialog::onBtnRelieveClicked()
{
    this->reject();
}