#include <QPainter>

#include "language.h"
#include "departmenttablewidget.h"


DepartmentTableWidget::DepartmentTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    // 行列数
    this->setRows(20);
    this->setColumns(2);
}

DepartmentTableWidget::~DepartmentTableWidget()
{

}

// 科室列表
void DepartmentTableWidget::setDepartments(const QList<Department>& departments)
{
    this->departments = departments;

    // 刷新
    this->update();
}

// 获取表头内容
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

// 获取表格内容
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