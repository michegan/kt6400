#ifndef _DEPARTMENT_TABLE_WIDGET_H_
#define _DEPARTMENT_TABLE_WIDGET_H_


#include "department.h"
#include "tablewidget.h"

class DepartmentTable;


// ���ұ��ؼ�
class DepartmentTableWidget : public TableWidget
{
    Q_OBJECT

public:
    DepartmentTableWidget(QWidget* parent = 0);
    virtual ~DepartmentTableWidget();

    // �����б�
    void setDepartments(const QList<Department>& departments);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:    
    // �����б�
    QList<Department> departments;
};


#endif // _DEPARTMENT_TABLE_WIDGET_H_