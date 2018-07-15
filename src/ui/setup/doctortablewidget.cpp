#include "language.h"
#include "doctortablewidget.h"


DoctorTableWidget::DoctorTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    // 行列数
    this->setRows(20);
    this->setColumns(3);
}

DoctorTableWidget::~DoctorTableWidget()
{

}

// 医生列表
void DoctorTableWidget::setDoctors(const QList<Doctor>& doctors)
{
    this->doctors = doctors;

    // 刷新
    this->update();
}

// 科室列表
void DoctorTableWidget::setDepartments(const QList<Department>& departments)
{
    this->departments = departments;

    // 刷新
    this->update();
}

// 获取表头内容
QStringList DoctorTableWidget::headText() const
{
    QStringList idses;
    idses << "IDS_DOCTOR_ID" << "IDS_DOCTOR_NAME" << "IDS_DEPARTMENT_NAME";

    QStringList heads;
    foreach (QString ids, idses)
    {
        heads.append(Language::getString(ids));
    }

    return heads;
}

// 获取表格内容
int DoctorTableWidget::numOfItems()
{
    return this->doctors.length();
}

QStringList DoctorTableWidget::rowText(int row)
{
    QStringList rowText;

    if (0 <= row && row < this->doctors.length())
    {
        const Doctor& doctor = this->doctors[row];

        rowText.append(doctor.doctorId);
        rowText.append(doctor.doctorName);
        rowText.append(this->deptName(doctor.deptId));
    }

    return rowText;
}

// 科室名称
QString DoctorTableWidget::deptName(const QString& deptId) const
{
    foreach (Department department, this->departments)
    {
        if (department.deptId == deptId)
        {
            return department.deptName;
        }
    }
    return "";
}