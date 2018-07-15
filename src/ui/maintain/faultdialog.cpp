#include "cache.h"
#include "faultid.h"
#include "faultdialog.h"


FaultDialog::FaultDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
    connect(ui.pbRelieve, SIGNAL(clicked()), this, SLOT(onBtnRelieveClicked()));
}

FaultDialog::~FaultDialog()
{

}

// 界面字符串
void FaultDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbRelieve, "IDS_RELIEVE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 按钮点击
void FaultDialog::onBtnCancelClicked()
{
    this->reject();
}

void FaultDialog::onBtnRelieveClicked()
{
    this->reject();
}