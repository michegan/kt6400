#ifndef _DOCTOR_TABLE_WIDGET_H_
#define _DOCTOR_TABLE_WIDGET_H_


#include "doctor.h"
#include "department.h"
#include "tablewidget.h"


// 医生表格控件
class DoctorTableWidget : public TableWidget
{
    Q_OBJECT

public:
    DoctorTableWidget(QWidget* parent = 0);
    virtual ~DoctorTableWidget();

    // 医生列表
    void setDoctors(const QList<Doctor>& doctors);
    // 科室列表
    void setDepartments(const QList<Department>& departments);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:
    // 科室名称
    QString deptName(const QString& deptCode) const;

private:    
    // 医生列表
    QList<Doctor> doctors;
    // 科室列表
    QList<Department> departments;
};


#endif // _DOCTOR_TABLE_WIDGET_H_