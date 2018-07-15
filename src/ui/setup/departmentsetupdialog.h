#ifndef _DEPARTMENT_SETUP_DIALOG_H_
#define _DEPARTMENT_SETUP_DIALOG_H_


#include "dialog.h"
#include "department.h"
#include "ui_departmentsetupdialog.h"

class DepartmentTable;
class DepartmentTableWidget;


// 科室设置对话框
class DepartmentSetupDialog : public Dialog
{
    Q_OBJECT

public:
    DepartmentSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DepartmentSetupDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 数据变化
    void onDepartmentTableDataChanged();

    // 按钮点击
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnCancelClicked();

private:
    // 科室信息
    QList<int> fids;
    QList<Department> departments;

    // 科室表
    DepartmentTable* departmentTable;
    // 科室列表
    DepartmentTableWidget* tableWidget;

    // 界面
    Ui::DepartmentSetupDialog ui;
};


#endif // _DEPARTMENT_SETUP_DIALOG_H_