#include <QtDebug>

#include "age.h"
#include "define.h"
#include "gender.h"
#include "datetime.h"
#include "messagebox.h"
#include "doctoreditdialog.h"


DoctorEditDialog::DoctorEditDialog(QWidget* parent)
    : Dialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 最大长度
    ui.leDoctorId->setMaxLength(MAX_USERNAME_LEN);
    ui.leDoctorName->setMaxLength(MAX_PASSWORD_LEN);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

DoctorEditDialog::~DoctorEditDialog()
{

}

// 样本信息
Doctor DoctorEditDialog::getDoctor()
{
    Doctor doctor;

    doctor.doctorId = ui.leDoctorId->text();
    doctor.doctorName = ui.leDoctorName->text();
    int index = ui.cbDeptName->currentIndex();
    doctor.deptId = (0 <= index ? this->departments.at(index).deptId : "");

    return doctor;
}

void DoctorEditDialog::setDoctor(const Doctor& doctor)
{
    ui.leDoctorId->setText(doctor.doctorId);
    ui.leDoctorName->setText(doctor.doctorName);

    for (int i = 0; i < this->departments.length(); i++)
    {
        if (this->departments[i].deptId == doctor.deptId)
        {
            ui.cbDeptName->setCurrentIndex(i);
            break;
        }
    }
}

// 科室列表
void DoctorEditDialog::setDepartments(const QList<Department>& departments)
{
    this->departments = departments;

    // 科室下拉框
    QStringList deptNames;
    foreach (Department department, departments)
    {
        deptNames.append(department.deptName);
    }
    ui.cbDeptName->insertItems(0, deptNames);

    // 刷新
    this->update();
}

// 界面字符串
void DoctorEditDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.lbDoctorId, "IDS_DOCTOR_ID");
    this->setText(ui.lbDoctorName, "IDS_DOCTOR_NAME");
    this->setText(ui.lbDeptName, "IDS_DEPARTMENT_NAME");
}

// 按钮点击
void DoctorEditDialog::onBtnOkClicked()
{
    this->accept();
}

void DoctorEditDialog::onBtnCancelClicked()
{
    this->reject();
}