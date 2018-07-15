#include "reviewdeletedialog.h"


ReviewDeleteDialog::ReviewDeleteDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

ReviewDeleteDialog::~ReviewDeleteDialog()
{

}

// 界面字符串
void ReviewDeleteDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();
    
    // 子类处理
    this->setText(ui.rbAll, "IDS_ALL_ITEMS");
    this->setText(ui.rbSelected, "IDS_SELECTED_ITEMS");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 选项
bool ReviewDeleteDialog::isDeleteAll() const
{
    return ui.rbAll->isChecked();
}