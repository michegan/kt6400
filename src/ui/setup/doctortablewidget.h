#ifndef _DOCTOR_TABLE_WIDGET_H_
#define _DOCTOR_TABLE_WIDGET_H_


#include "doctor.h"
#include "department.h"
#include "tablewidget.h"


// ҽ�����ؼ�
class DoctorTableWidget : public TableWidget
{
    Q_OBJECT

public:
    DoctorTableWidget(QWidget* parent = 0);
    virtual ~DoctorTableWidget();

    // ҽ���б�
    void setDoctors(const QList<Doctor>& doctors);
    // �����б�
    void setDepartments(const QList<Department>& departments);

protected:
    // ��ȡ��ͷ����
    virtual QStringList headText() const;

    // ��ȡ�������
    virtual int numOfItems();
    virtual QStringList rowText(int row);

private:
    // ��������
    QString deptName(const QString& deptCode) const;

private:    
    // ҽ���б�
    QList<Doctor> doctors;
    // �����б�
    QList<Department> departments;
};


#endif // _DOCTOR_TABLE_WIDGET_H_