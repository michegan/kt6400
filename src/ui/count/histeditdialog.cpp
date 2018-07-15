#include "histeditdialog.h"


HistEditDialog::HistEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 直方图控件
    this->wbcHistWidget = new WbcHistWidget(this);
    this->wbcHistWidget->setGeometry(20, 20, 230, 150);

    this->rbcHistWidget = new RbcHistWidget(this);
    this->rbcHistWidget->setGeometry(20, 160, 230, 150);

    this->pltHistWidget = new PltHistWidget(this);
    this->pltHistWidget->setGeometry(20, 320, 230, 150);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

HistEditDialog::~HistEditDialog()
{

}

// 按钮点击
void HistEditDialog::onBtnOkClicked()
{
    // 关闭对话框
    this->accept();
}

void HistEditDialog::onBtnCancelClicked()
{
    this->reject();
}