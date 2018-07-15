#ifndef _DOCTOR_SETUP_DIALOG_H_
#define _DOCTOR_SETUP_DIALOG_H_


#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "ui_doctorsetupdialog.h"

class DoctorTable;
class DoctorTableWidget;


// 医生设置对话框
class DoctorSetupDialog : public Dialog
{
    Q_OBJECT

public:
    DoctorSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DoctorSetupDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 数据变化
    void onDoctorTableDataChanged();

    // 按钮点击
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnDeleteClicked();
    virtual void onBtnCancelClicked();

private:
    // 医生信息
    QList<int> fids;
    QList<Doctor> doctors;

    // 科室信息
    QList<Department> departments;

    // 医生表
    DoctorTable* doctorTable;
    // 医生列表
    DoctorTableWidget* tableWidget;

    // 界面
    Ui::DoctorSetupDialog ui;
};


#endif // _DOCTOR_SETUP_DIALOG_H_