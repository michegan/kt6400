#include "modeeditdialog.h"


ModeEditDialog::ModeEditDialog(QWidget* parent)
    : Dialog(parent), modes(Modes())
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

ModeEditDialog::~ModeEditDialog()
{

}

// 模式
Modes ModeEditDialog::getModes() const
{
    return this->modes;
}

void ModeEditDialog::setModes(const Modes& modes)
{
    // 模式变量
    this->modes = modes;

    // 界面显示
    if (PREPROCESS_MODE_PREDILUENT == modes.preprocessMode)
    {
        ui.rbPrediluent->setChecked(true);
    }
    else
    {
        ui.rbPeripheral->setChecked(BLOOD_MODE_PERIPHERAL == modes.bloodMode);
        ui.rbWholeBlood->setChecked(BLOOD_MODE_PERIPHERAL != modes.bloodMode);
    }
}

// 界面字符串
void ModeEditDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    ui.gbMode->setTitle(this->getString("IDS_MODE"));

    this->setText(ui.rbWholeBlood, "IDS_WHOLE_BLOOD");
    this->setText(ui.rbPeripheral, "IDS_PERIPHERAL");
    this->setText(ui.rbPrediluent, "IDS_PREDILUENT");

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 按钮点击
void ModeEditDialog::onBtnOkClicked()
{
    // 获取模式
    if (ui.rbPrediluent->isChecked())
    {
        this->modes.bloodMode = BLOOD_MODE_PERIPHERAL;
        this->modes.preprocessMode = PREPROCESS_MODE_PREDILUENT;
    }
    else
    {
        this->modes.preprocessMode = PREPROCESS_MODE_NONE;
        if (ui.rbPeripheral->isChecked())
        {
            this->modes.bloodMode = BLOOD_MODE_PERIPHERAL;
        }
        else
        {
            this->modes.bloodMode = BLOOD_MODE_WHOLE_BLOOD;
        }
    }

    // 关闭对话框
    this->accept();
}

void ModeEditDialog::onBtnCancelClicked()
{
    this->reject();
}