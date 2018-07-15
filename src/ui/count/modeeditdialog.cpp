#include "modeeditdialog.h"


ModeEditDialog::ModeEditDialog(QWidget* parent)
    : Dialog(parent), modes(Modes())
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

ModeEditDialog::~ModeEditDialog()
{

}

// ģʽ
Modes ModeEditDialog::getModes() const
{
    return this->modes;
}

void ModeEditDialog::setModes(const Modes& modes)
{
    // ģʽ����
    this->modes = modes;

    // ������ʾ
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

// �����ַ���
void ModeEditDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    ui.gbMode->setTitle(this->getString("IDS_MODE"));

    this->setText(ui.rbWholeBlood, "IDS_WHOLE_BLOOD");
    this->setText(ui.rbPeripheral, "IDS_PERIPHERAL");
    this->setText(ui.rbPrediluent, "IDS_PREDILUENT");

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ��ť���
void ModeEditDialog::onBtnOkClicked()
{
    // ��ȡģʽ
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

    // �رնԻ���
    this->accept();
}

void ModeEditDialog::onBtnCancelClicked()
{
    this->reject();
}