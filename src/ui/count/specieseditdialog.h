#ifndef _SPECIES_EDIT_DIALOG_H_
#define _SPECIES_EDIT_DIALOG_H_


#include "modes.h"
#include "dialog.h"
#include "ui_specieseditdialog.h"


// 物种编辑对话框
class SpeciesEditDialog : public Dialog
{
    Q_OBJECT

public:
    SpeciesEditDialog(QWidget* parent = 0);
    virtual ~SpeciesEditDialog();

    // 模式
    int speciesMode() const;
    void setSpeciesMode(int speciesMode);

protected:
    // 界面字符串
    virtual void setWindowText();

private:
    // 界面
    Ui::SpeciesEditDialog ui;

    // 物种控件
    QMap<int, QRadioButton*> buttons;
};


#endif // _SPECIES_EDIT_DIALOG_H_