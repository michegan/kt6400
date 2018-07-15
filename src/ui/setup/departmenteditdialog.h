#ifndef _DEPARTMENT_EDIT_DIALOG_H_
#define _DEPARTMENT_EDIT_DIALOG_H_


#include "dialog.h"
#include "department.h"
#include "ui_departmenteditdialog.h"


// ���ұ༭�Ի���
class DepartmentEditDialog : public Dialog
{
    Q_OBJECT

public:
    DepartmentEditDialog(QWidget* parent = 0);
    virtual ~DepartmentEditDialog();

    // ������Ϣ
    Department getDepartment();
    void setDepartment(const Department& department);

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ����
    Ui::DepartmentEditDialog ui;
};


#endif // _DEPARTMENT_EDIT_DIALOG_H_