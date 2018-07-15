#include "helpdialog.h"


HelpDialog::HelpDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
}

HelpDialog::~HelpDialog()
{

}

// 按钮点击
void HelpDialog::onBtnOkClicked()
{
    this->reject();
}

void HelpDialog::onBtnPageUpClicked()
{

}

void HelpDialog::onBtnPageDownClicked()
{

}