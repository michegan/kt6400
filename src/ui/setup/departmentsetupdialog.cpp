#include <QtDebug>

#include "messagebox.h"
#include "departmenttable.h"
#include "departmenteditdialog.h"
#include "departmentsetupdialog.h"
#include "departmenttablewidget.h"


DepartmentSetupDialog::DepartmentSetupDialog(QWidget* parent, Qt::WFlags flags)
    : Dialog(parent), departmentTable(new DepartmentTable()), tableWidget(new DepartmentTableWidget(this))
{
    ui.setupUi(this);

    // 科室列表
    this->tableWidget->setGeometry(20, 20, 420, 460);

    // 加载所有科室信息
    this->onDepartmentTableDataChanged();

    // 关联信号槽
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->departmentTable, SIGNAL(dataChanged()), this, SLOT(onDepartmentTableDataChanged()));
}

DepartmentSetupDialog::~DepartmentSetupDialog()
{

}

// 界面字符串
void DepartmentSetupDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 数据变化
void DepartmentSetupDialog::onDepartmentTableDataChanged()
{
    // 系统所有科室
    this->fids = this->departmentTable->departments();

    // 满足条件的科室才显示在科室表格中
    this->departments.clear();

    foreach (int fid, this->fids)
    {
        Department department;
        if (this->departmentTable->department(fid, department.deptId, department.deptName))
        {
            departments.append(department);
        }
    }

    // 刷新科室列表
    this->tableWidget->setDepartments(this->departments);
}

// 按钮点击
void DepartmentSetupDialog::onBtnAddClicked()
{
    DepartmentEditDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        // 新科室
        Department department = dialog.getDepartment();

        // 科室名是否重复
        QList<int> fids = this->departmentTable->fids(department.deptName);
        if (0 < fids.length())
        {
            // 科室名重复，不能新增
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // 保存到数据库
            int fid = 0;
            this->departmentTable->insertDepartment(fid, department.deptId, department.deptName);
        }
    }
}

void DepartmentSetupDialog::onBtnEditClicked()
{
    // 可以编辑当前科室
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        DepartmentEditDialog dialog(this);

        dialog.setDepartment(this->departments[row]);
        if (QDialog::Accepted == dialog.exec())
        {
            // 新科室
            Department department = dialog.getDepartment();

            // 科室名是否重复
            QList<int> fids = this->departmentTable->fids(department.deptName);
            if (1 < fids.length())
            {
                // 科室名重复，不能新增
                MessageBox::warningIds(this, "IDS_USER_EXIST");
            }
            else
            {
                this->departmentTable->updateDepartment(this->fids.at(row), department.deptId, department.deptName);
            }
        }
    }
}

void DepartmentSetupDialog::onBtnCancelClicked()
{
    this->reject();
}