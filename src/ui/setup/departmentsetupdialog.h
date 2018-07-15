#ifndef _DEPARTMENT_SETUP_DIALOG_H_
#define _DEPARTMENT_SETUP_DIALOG_H_


#include "dialog.h"
#include "department.h"
#include "ui_departmentsetupdialog.h"

class DepartmentTable;
class DepartmentTableWidget;


// �������öԻ���
class DepartmentSetupDialog : public Dialog
{
    Q_OBJECT

public:
    DepartmentSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DepartmentSetupDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ���ݱ仯
    void onDepartmentTableDataChanged();

    // ��ť���
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnCancelClicked();

private:
    // ������Ϣ
    QList<int> fids;
    QList<Department> departments;

    // ���ұ�
    DepartmentTable* departmentTable;
    // �����б�
    DepartmentTableWidget* tableWidget;

    // ����
    Ui::DepartmentSetupDialog ui;
};


#endif // _DEPARTMENT_SETUP_DIALOG_H_