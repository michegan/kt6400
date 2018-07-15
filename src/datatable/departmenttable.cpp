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

// �����б�
QList<int> DepartmentTable::departments()
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

// ������Ϣ
QList<int> DepartmentTable::fids(const QString& deptName)
{
    QList<int> fids;

    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_DEPT_NAME, deptName);

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

// ������Ϣ
bool DepartmentTable::department(int fid, QString& deptName, QString& deptId)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();

        deptId = record.value(F_DEPT_ID).toString();
        deptName = record.value(F_DEPT_NAME).toString();

        ret = true;
    }

    return ret;
}

// ��������
bool DepartmentTable::insertDepartment(int& fid, const QString& deptName, const QString& deptId)
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
        record.setValue(F_DEPT_ID, deptId);
        record.setValue(F_DEPT_NAME, deptName);

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

// ɾ������
bool DepartmentTable::deleteDepartment(int fid)
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ����¼
    return this->deleteRecord();
}

// ���Ŀ�����Ϣ
bool DepartmentTable::updateDepartment(int fid, const QString& deptName, const QString& deptId)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        record.setValue(F_DEPT_ID, deptId);
        record.setValue(F_DEPT_NAME, deptName);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}