#include "helpdialog.h"


HelpDialog::HelpDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
}

HelpDialog::~HelpDialog()
{

}

// ��ť���
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