#include <QPainter>

#include "language.h"
#include "departmenttablewidget.h"


DepartmentTableWidget::DepartmentTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    // ������
    this->setRows(20);
    this->setColumns(2);
}

DepartmentTableWidget::~DepartmentTableWidget()
{

}

// �����б�
void DepartmentTableWidget::setDepartments(const QList<Department>& departments)
{
    this->departments = departments;

    // ˢ��
    this->update();
}

// ��ȡ��ͷ����
QStringList DepartmentTableWidget::headText() const
{
    QStringList idses;
    idses << "IDS_DEPARTMENT_ID" << "IDS_DEPARTMENT_NAME";

    QStringList heads;
    foreach (QString ids, idses)
    {
        heads.append(Language::getString(ids));
    }

    return heads;
}

// ��ȡ�������
int DepartmentTableWidget::numOfItems()
{
    return this->departments.length();
}

QStringList DepartmentTableWidget::rowText(int row)
{
    QStringList rowText;

    if (0 <= row && row < this->departments.length())
    {
        const Department& department = this->departments[row];

        rowText.append(department.deptId);
        rowText.append(department.deptName);
    }

    return rowText;
}