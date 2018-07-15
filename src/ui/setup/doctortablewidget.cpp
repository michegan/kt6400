#include "language.h"
#include "doctortablewidget.h"


DoctorTableWidget::DoctorTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    // ������
    this->setRows(20);
    this->setColumns(3);
}

DoctorTableWidget::~DoctorTableWidget()
{

}

// ҽ���б�
void DoctorTableWidget::setDoctors(const QList<Doctor>& doctors)
{
    this->doctors = doctors;

    // ˢ��
    this->update();
}

// �����б�
void DoctorTableWidget::setDepartments(const QList<Department>& departments)
{
    this->departments = departments;

    // ˢ��
    this->update();
}

// ��ȡ��ͷ����
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

// ��ȡ�������
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

// ��������
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