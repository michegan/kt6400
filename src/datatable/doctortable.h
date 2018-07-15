#ifndef _DOCTOR_TABLE_H_
#define _DOCTOR_TABLE_H_


#include "datatable.h"
#include "libdatatable.h"


// ҽ��������ݱ�
class DATATABLE_EXPORT DoctorTable : public DataTable
{
public:
    DoctorTable();
    virtual ~DoctorTable();

    // ҽ���б�
    QList<int> doctors();

    // ҽ����Ϣ
    QList<int> fids(const QString& doctorId);

    // ҽ����Ϣ
    bool doctor(int fid, QString& doctorId, QString& doctorName, QString& deptId);

    // ����ҽ��
    bool insertDoctor(int& fid, const QString& doctorId, const QString& doctorName, const QString& deptId);

    // ɾ��ҽ��
    bool deleteDoctor(int fid);

    // ����ҽ����Ϣ
    bool updateDoctor(int fid, const QString& doctorId, const QString& doctorName, const QString& deptId);
};


#endif // _DOCTOR_TABLE_H_