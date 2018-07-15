#include <QtDebug>

#include "messagebox.h"
#include "doctortable.h"
#include "departmenttable.h"
#include "doctoreditdialog.h"
#include "doctorsetupdialog.h"
#include "doctortablewidget.h"


DoctorSetupDialog::DoctorSetupDialog(QWidget* parent, Qt::WFlags flags)
    : Dialog(parent), doctorTable(new DoctorTable()), tableWidget(new DoctorTableWidget(this))
{
    ui.setupUi(this);

    // 科室列表
    DepartmentTable departmentTable;
    QList<int> fids = departmentTable.departments();

    // 满足条件的科室才显示在科室表格中
    foreach (int fid, fids)
    {
        Department department;
        if (departmentTable.department(fid, department.deptId, department.deptName))
        {
            this->departments.append(department);
        }
    }

    // 医生列表
    this->tableWidget->setGeometry(20, 20, 420, 460);
    this->tableWidget->setDepartments(this->departments);

    // 加载所有医生信息
    this->onDoctorTableDataChanged();

    // 关联信号槽
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->doctorTable, SIGNAL(dataChanged()), this, SLOT(onDoctorTableDataChanged()));
}

DoctorSetupDialog::~DoctorSetupDialog()
{

}

// 界面字符串
void DoctorSetupDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 数据变化
void DoctorSetupDialog::onDoctorTableDataChanged()                        
{
    // 系统所有医生
    this->fids = this->doctorTable->doctors();

    // 满足条件的医生才显示在医生表格中
    this->doctors.clear();

    foreach (int fid, this->fids)
    {
        Doctor doctor;
        if (this->doctorTable->doctor(fid, doctor.doctorId, doctor.doctorName, doctor.deptId))
        {
            doctors.append(doctor);
        }
    }

    // 刷新医生列表
    this->tableWidget->setDoctors(this->doctors);
}

// 按钮点击
void DoctorSetupDialog::onBtnAddClicked()
{
    DoctorEditDialog dialog(this);

    dialog.setDepartments(this->departments);

    if (QDialog::Accepted == dialog.exec())
    {
        // 新医生
        Doctor doctor = dialog.getDoctor();

        // 医生名是否重复
        QList<int> fids = this->doctorTable->fids(doctor.doctorName);
        if (0 < fids.length())
        {
            // 医生名重复，不能新增
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // 保存到数据库
            int fid = 0;
            this->doctorTable->insertDoctor(fid, doctor.doctorId, doctor.doctorName, doctor.deptId);
        }
    }
}

void DoctorSetupDialog::onBtnEditClicked()
{
    // 可以编辑当前医生
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        DoctorEditDialog dialog(this);

        dialog.setDepartments(this->departments);
        dialog.setDoctor(this->doctors[row]);

        if (QDialog::Accepted == dialog.exec())
        {
            // 新医生
            Doctor doctor = dialog.getDoctor();

            // 医生名是否重复
            QList<int> fids = this->doctorTable->fids(doctor.doctorName);
            if (1 < fids.length())
            {
                // 医生名重复，不能新增
                MessageBox::warningIds(this, "IDS_USER_EXIST");
            }
            else
            {
                this->doctorTable->updateDoctor(this->fids.at(row), doctor.doctorId, doctor.doctorName, doctor.deptId);
            }
        }
    }
}

void DoctorSetupDialog::onBtnDeleteClicked()
{
    // 可以删除当前医生
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        this->doctorTable->deleteDoctor(this->fids.at(row));
    }
}

void DoctorSetupDialog::onBtnCancelClicked()
{
    this->reject();
}