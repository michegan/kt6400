#ifndef _DOCTOR_TABLE_H_
#define _DOCTOR_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// 医生相关数据表
class DATATABLE_EXPORT DoctorTable : public DataTable
{
public:
    DoctorTable();
    virtual ~DoctorTable();

    // 医生列表
    QList<int> doctors();

    // 医生信息
    QList<int> fids(const QString& doctorId);

    // 医生信息
    bool doctor(int fid, QString& doctorId, QString& doctorName, QString& deptId);

    // 新增医生
    bool insertDoctor(int& fid, const QString& doctorId, const QString& doctorName, const QString& deptId);

    // 删除医生
    bool deleteDoctor(int fid);

    // 更改医生信息
    bool updateDoctor(int fid, const QString& doctorId, const QString& doctorName, const QString& deptId);
};


#endif // _DOCTOR_TABLE_H_