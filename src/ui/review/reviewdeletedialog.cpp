#include "reviewdeletedialog.h"


ReviewDeleteDialog::ReviewDeleteDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

ReviewDeleteDialog::~ReviewDeleteDialog()
{

}

// �����ַ���
void ReviewDeleteDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();
    
    // ���ദ��
    this->setText(ui.rbAll, "IDS_ALL_ITEMS");
    this->setText(ui.rbSelected, "IDS_SELECTED_ITEMS");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ѡ��
bool ReviewDeleteDialog::isDeleteAll() const
{
    return ui.rbAll->isChecked();
}