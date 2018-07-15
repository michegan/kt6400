#ifndef _DEPARTMENT_TABLE_H_
#define _DEPARTMENT_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// 科室相关数据表
class DATATABLE_EXPORT DepartmentTable : public DataTable
{
public:
    DepartmentTable();
    virtual ~DepartmentTable();

    // 科室列表
    QList<int> departments();

    // 科室信息
    QList<int> fids(const QString& deptName);

    // 科室信息
    bool department(int fid, QString& deptName, QString& deptId);

    // 新增科室
    bool insertDepartment(int& fid, const QString& deptName, const QString& deptId);

    // 删除科室
    bool deleteDepartment(int fid);

    // 更改科室信息
    bool updateDepartment(int fid, const QString& deptName, const QString& deptId);
};


#endif // _DEPARTMENT_TABLE_H_