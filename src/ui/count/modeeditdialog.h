#ifndef _MODE_EDIT_DIALOG_H_
#define _MODE_EDIT_DIALOG_H_


#include "modes.h"
#include "dialog.h"
#include "ui_modeeditdialog.h"


// ģʽ�༭�Ի���
class ModeEditDialog : public Dialog
{
    Q_OBJECT

public:
    ModeEditDialog(QWidget* parent = 0);
    virtual ~ModeEditDialog();

    // ģʽ
    Modes getModes() const;
    void setModes(const Modes& modes);

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ģʽ
    Modes modes;

    // ����
    Ui::ModeEditDialog ui;
};


#endif // _MODE_EDIT_DIALOG_H_