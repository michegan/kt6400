#ifndef _DEPARTMENT_TABLE_WIDGET_H_
#define _DEPARTMENT_TABLE_WIDGET_H_


#include "department.h"
#include "tablewidget.h"

class DepartmentTable;


// 科室表格控件
class DepartmentTableWidget : public TableWidget
{
    Q_OBJECT

public:
    DepartmentTableWidget(QWidget* parent = 0);
    virtual ~DepartmentTableWidget();

    // 科室列表
    void setDepartments(const QList<Department>& departments);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:    
    // 科室列表
    QList<Department> departments;
};


#endif // _DEPARTMENT_TABLE_WIDGET_H_