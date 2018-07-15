#include <QtDebug>

#include "field.h"
#include "doctortable.h"


DoctorTable::DoctorTable()
    : DataTable("T_DOCTOR")
{

}

DoctorTable::~DoctorTable()
{

}

// 医生列表
QList<int> DoctorTable::doctors()
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

// 医生信息
QList<int> DoctorTable::fids(const QString& doctorId)
{
    QList<int> fids;

    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_DOCTOR_ID, doctorId);

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

// 医生信息
bool DoctorTable::doctor(int fid, QString& doctorId, QString& doctorName, QString& deptId)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        doctorId = record.value(F_DOCTOR_ID).toString();
        doctorName = record.value(F_DOCTOR_NAME).toString();
        deptId = record.value(F_DEPT_ID).toString();

        ret = true;
    }

    return ret;
}

// 新增医生
bool DoctorTable::insertDoctor(int& fid, const QString& doctorId, const QString& doctorName, const QString& deptId)
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
        record.setValue(F_DOCTOR_ID, doctorId);
        record.setValue(F_DOCTOR_NAME, doctorName);
        record.setValue(F_DEPT_ID, deptId);

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

// 删除医生
bool DoctorTable::deleteDoctor(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除记录
    return this->deleteRecord();
}

// 更改医生信息
bool DoctorTable::updateDoctor(int fid, const QString& doctorId, const QString& doctorName, const QString& deptId)
{
    bool ret = false;

    // 查询上述条件记录（只应该查询到1条记录）
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // 更新需要更新的字段
        QSqlRecord record = query.record();

        record.setValue(F_DOCTOR_ID, doctorId);
        record.setValue(F_DOCTOR_NAME, doctorName);
        record.setValue(F_DEPT_ID, deptId);

        // 执行对应SQL操作
        ret = this->updateRecord(record);
    }

    return ret;
}