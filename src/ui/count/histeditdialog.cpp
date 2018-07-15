#include "histeditdialog.h"


HistEditDialog::HistEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // ֱ��ͼ�ؼ�
    this->wbcHistWidget = new WbcHistWidget(this);
    this->wbcHistWidget->setGeometry(20, 20, 230, 150);

    this->rbcHistWidget = new RbcHistWidget(this);
    this->rbcHistWidget->setGeometry(20, 160, 230, 150);

    this->pltHistWidget = new PltHistWidget(this);
    this->pltHistWidget->setGeometry(20, 320, 230, 150);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

HistEditDialog::~HistEditDialog()
{

}

// ��ť���
void HistEditDialog::onBtnOkClicked()
{
    // �رնԻ���
    this->accept();
}

void HistEditDialog::onBtnCancelClicked()
{
    this->reject();
}