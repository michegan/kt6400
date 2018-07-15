#include <QtDebug>

#include "define.h"
#include "messagebox.h"
#include "departmenteditdialog.h"


DepartmentEditDialog::DepartmentEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ��󳤶�

    // ��󳤶�
    ui.leDeptName->setMaxLength(MAX_USERNAME_LEN);
    ui.leDeptName->setMaxLength(MAX_PASSWORD_LEN);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

DepartmentEditDialog::~DepartmentEditDialog()
{

}

// ������Ϣ
Department DepartmentEditDialog::getDepartment()
{
    Department department;

    department.deptId = ui.leDeptId->text();
    department.deptName = ui.leDeptName->text();

    return department;
}

void DepartmentEditDialog::setDepartment(const Department& department)
{
    ui.leDeptId->setText(department.deptId);
    ui.leDeptName->setText(department.deptName);
}

// �����ַ���
void DepartmentEditDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.lbDeptId, "IDS_DEPARTMENT_ID");
    this->setText(ui.lbDeptName, "IDS_DEPARTMENT_NAME");
}

// ��ť���
void DepartmentEditDialog::onBtnOkClicked()
{
    this->accept();
}

void DepartmentEditDialog::onBtnCancelClicked()
{
    this->reject();
}