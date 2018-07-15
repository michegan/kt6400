#ifndef _DEPARTMENT_TABLE_H_
#define _DEPARTMENT_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// ����������ݱ�
class DATATABLE_EXPORT DepartmentTable : public DataTable
{
public:
    DepartmentTable();
    virtual ~DepartmentTable();

    // �����б�
    QList<int> departments();

    // ������Ϣ
    QList<int> fids(const QString& deptName);

    // ������Ϣ
    bool department(int fid, QString& deptName, QString& deptId);

    // ��������
    bool insertDepartment(int& fid, const QString& deptName, const QString& deptId);

    // ɾ������
    bool deleteDepartment(int fid);

    // ���Ŀ�����Ϣ
    bool updateDepartment(int fid, const QString& deptName, const QString& deptId);
};


#endif // _DEPARTMENT_TABLE_H_