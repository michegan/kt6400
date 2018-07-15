#ifndef _DOCTOR_EDIT_DIALOG_H_
#define _DOCTOR_EDIT_DIALOG_H_


#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "ui_doctoreditdialog.h"


// 医生编辑对话框
class DoctorEditDialog : public Dialog
{
    Q_OBJECT

public:
    DoctorEditDialog(QWidget* parent = 0);
    virtual ~DoctorEditDialog();

    // 医生信息
    Doctor getDoctor();
    void setDoctor(const Doctor& doctor);
    // 科室列表
    void setDepartments(const QList<Department>& departments);

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 界面
    Ui::DoctorEditDialog ui;
    // 科室列表
    QList<Department> departments;
};


#endif // _DOCTOR_EDIT_DIALOG_H_