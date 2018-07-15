#include <QtDebug>

#include "field.h"
#include "departmenttable.h"


DepartmentTable::DepartmentTable()
    : DataTable("T_DEPARTMENT")
{

}

DepartmentTable::~DepartmentTable()
{

}

// 科室列表
QList<int> DepartmentTable::departments()
{
    QList<int> fids;

    // 查询条件
    this->clearConditions();

    // 删除
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();
        fids.append(record.value(F_ID).toInt());
    }

    return fids;
}

// 科室信息
QList<int> DepartmentTable::fids(const QString& deptName)
{
    QList<int> fids;

    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_DEPT_NAME, deptName);

    // 删除
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        int fid = record.value(F_ID).toInt();
        fids.append(fid);
    }

    return fids;
}

// 科室信息
bool DepartmentTable::department(int fid, QString& deptName, QString& deptId)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        deptId = record.value(F_DEPT_ID).toString();
        deptName = record.value(F_DEPT_NAME).toString();

        ret = true;
    }

    return ret;
}

// 新增科室
bool DepartmentTable::insertDepartment(int& fid, const QString& deptName, const QString& deptId)
{
    bool ret = false;

    do 
    {
        // 下一F_ID
        int nid = this->nextFid();
        if (nid <= 0)
        {
            break;
        }

        // 表对应记录
        QSqlRecord record = this->record();
        record.clearValues();

        // 更新需要更新的字段
        record.setValue(F_ID, nid);
        record.setValue(F_DEPT_ID, deptId);
        record.setValue(F_DEPT_NAME, deptName);

        // 执行对应SQL操作
        if (!this->insertRecord(record))
        {
            break;
        }

        ret = true;
        fid = nid;
    } while (0);

    return ret;
}

// 删除科室
bool DepartmentTable::deleteDepartment(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除记录
    return this->deleteRecord();
}

// 更改科室信息
bool DepartmentTable::updateDepartment(int fid, const QString& deptName, const QString& deptId)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 更新需要更新的字段
        QSqlRecord record = query.record();

        record.setValue(F_DEPT_ID, deptId);
        record.setValue(F_DEPT_NAME, deptName);

        // 执行对应SQL操作
        ret = this->updateRecord(record);
    }

    return ret;
}