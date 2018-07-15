#include "specieseditdialog.h"


SpeciesEditDialog::SpeciesEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ���ֿؼ�
    this->buttons.insert(SPECIES_MODE_CAT, ui.rbCat);
    this->buttons.insert(SPECIES_MODE_DOG, ui.rbDog);
    this->buttons.insert(SPECIES_MODE_MOUSE, ui.rbMouse);
    this->buttons.insert(SPECIES_MODE_RABBIT, ui.rbRabbit);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

SpeciesEditDialog::~SpeciesEditDialog()
{

}

// ģʽ
int SpeciesEditDialog::speciesMode() const
{
    QList<QRadioButton*> buttons = this->buttons.values();

    foreach (QRadioButton* button, buttons)
    {
        if (button->isChecked())
        {
            return this->buttons.key(button);
        }
    }

    return SPECIES_MODE_UNKNOWN;
}

void SpeciesEditDialog::setSpeciesMode(int speciesMode)
{
    QList<int> animals = this->buttons.keys();

    foreach (int animal, animals)
    {
        QRadioButton* button = this->buttons.value(animal);
        button->setChecked(animal == speciesMode);
    }
}

// �����ַ���
void SpeciesEditDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    ui.gbSpecies->setTitle(this->getString("IDS_SPECIES"));

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");

    // ���ֿؼ�
    QMap<int, QLabel*> labels;

    labels.insert(SPECIES_MODE_CAT, ui.lbCat);
    labels.insert(SPECIES_MODE_DOG, ui.lbDog);
    labels.insert(SPECIES_MODE_MOUSE, ui.lbMouse);
    labels.insert(SPECIES_MODE_RABBIT, ui.lbRabbit);

    QList<int> animals = labels.keys();
    foreach (int animal, animals)
    {
        QLabel* label = labels.value(animal);

        Modes modes;
        modes.speciesMode = animal;

        QPixmap pixmap("./image/" + modes.speciesImage());
        pixmap = pixmap.scaled(label->height(), label->height());

        label->setPixmap(pixmap);
        label->setWindowOpacity(0);
    }
}