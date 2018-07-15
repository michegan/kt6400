#ifndef _SPECIES_EDIT_DIALOG_H_
#define _SPECIES_EDIT_DIALOG_H_


#include "modes.h"
#include "dialog.h"
#include "ui_specieseditdialog.h"


// ���ֱ༭�Ի���
class SpeciesEditDialog : public Dialog
{
    Q_OBJECT

public:
    SpeciesEditDialog(QWidget* parent = 0);
    virtual ~SpeciesEditDialog();

    // ģʽ
    int speciesMode() const;
    void setSpeciesMode(int speciesMode);

protected:
    // �����ַ���
    virtual void setWindowText();

private:
    // ����
    Ui::SpeciesEditDialog ui;

    // ���ֿؼ�
    QMap<int, QRadioButton*> buttons;
};


#endif // _SPECIES_EDIT_DIALOG_H_