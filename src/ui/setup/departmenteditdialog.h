#ifndef _DEPARTMENT_EDIT_DIALOG_H_
#define _DEPARTMENT_EDIT_DIALOG_H_


#include "dialog.h"
#include "department.h"
#include "ui_departmenteditdialog.h"


// 科室编辑对话框
class DepartmentEditDialog : public Dialog
{
    Q_OBJECT

public:
    DepartmentEditDialog(QWidget* parent = 0);
    virtual ~DepartmentEditDialog();

    // 科室信息
    Department getDepartment();
    void setDepartment(const Department& department);

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 界面
    Ui::DepartmentEditDialog ui;
};


#endif // _DEPARTMENT_EDIT_DIALOG_H_