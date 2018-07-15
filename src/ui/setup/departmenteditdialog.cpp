#include <QtDebug>

#include "define.h"
#include "messagebox.h"
#include "departmenteditdialog.h"


DepartmentEditDialog::DepartmentEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 最大长度

    // 最大长度
    ui.leDeptName->setMaxLength(MAX_USERNAME_LEN);
    ui.leDeptName->setMaxLength(MAX_PASSWORD_LEN);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

DepartmentEditDialog::~DepartmentEditDialog()
{

}

// 样本信息
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

// 界面字符串
void DepartmentEditDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.lbDeptId, "IDS_DEPARTMENT_ID");
    this->setText(ui.lbDeptName, "IDS_DEPARTMENT_NAME");
}

// 按钮点击
void DepartmentEditDialog::onBtnOkClicked()
{
    this->accept();
}

void DepartmentEditDialog::onBtnCancelClicked()
{
    this->reject();
}