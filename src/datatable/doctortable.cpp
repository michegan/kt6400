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

// ҽ���б�
QList<int> DoctorTable::doctors()
{
    QList<int> fids;

    // ��ѯ����
    this->clearConditions();

    // ɾ��
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();
        fids.append(record.value(F_ID).toInt());
    }

    return fids;
}

// ҽ����Ϣ
QList<int> DoctorTable::fids(const QString& doctorId)
{
    QList<int> fids;

    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_DOCTOR_ID, doctorId);

    // ɾ��
    QSqlQuery query = this->selectRecord();
    while (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();

        int fid = record.value(F_ID).toInt();
        fids.append(fid);
    }

    return fids;
}

// ҽ����Ϣ
bool DoctorTable::doctor(int fid, QString& doctorId, QString& doctorName, QString& deptId)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();

        doctorId = record.value(F_DOCTOR_ID).toString();
        doctorName = record.value(F_DOCTOR_NAME).toString();
        deptId = record.value(F_DEPT_ID).toString();

        ret = true;
    }

    return ret;
}

// ����ҽ��
bool DoctorTable::insertDoctor(int& fid, const QString& doctorId, const QString& doctorName, const QString& deptId)
{
    bool ret = false;

    do 
    {
        // ��һF_ID
        int nid = this->nextFid();
        if (nid <= 0)
        {
            break;
        }

        // ���Ӧ��¼
        QSqlRecord record = this->record();
        record.clearValues();

        // ������Ҫ���µ��ֶ�
        record.setValue(F_ID, nid);
        record.setValue(F_DOCTOR_ID, doctorId);
        record.setValue(F_DOCTOR_NAME, doctorName);
        record.setValue(F_DEPT_ID, deptId);

        // ִ�ж�ӦSQL����
        if (!this->insertRecord(record))
        {
            break;
        }

        ret = true;
        fid = nid;
    } while (0);

    return ret;
}

// ɾ��ҽ��
bool DoctorTable::deleteDoctor(int fid)
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ����¼
    return this->deleteRecord();
}

// ����ҽ����Ϣ
bool DoctorTable::updateDoctor(int fid, const QString& doctorId, const QString& doctorName, const QString& deptId)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        record.setValue(F_DOCTOR_ID, doctorId);
        record.setValue(F_DOCTOR_NAME, doctorName);
        record.setValue(F_DEPT_ID, deptId);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}