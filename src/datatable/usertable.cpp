#include <QtDebug>

#include "field.h"
#include "usertable.h"


UserTable::UserTable()
    : DataTable("T_USER")
{

}

UserTable::~UserTable()
{

}

// �û��б�
QList<int> UserTable::users()
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

// �û���Ϣ
QList<int> UserTable::fids(const QString& userName)
{
    QList<int> fids;

    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_USERNAME, userName);

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

// �û���Ϣ
bool UserTable::user(int fid, QString& userName, QString& fullName, QString& password, int& level)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();

        userName = record.value(F_USERNAME).toString();
        fullName = record.value(F_FULLNAME).toString();
        password = record.value(F_PASSWORD).toString();
        level = record.value(F_USERLEVEL).toInt();

        ret = true;
    }

    return ret;
}

// �����û�
bool UserTable::insertUser(int& fid, const QString& userName, const QString& fullName, const QString& password, int level)
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
        record.setValue(F_USERNAME, userName);
        record.setValue(F_FULLNAME, fullName);
        record.setValue(F_PASSWORD, password);
        record.setValue(F_USERLEVEL, level);

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

// ɾ���û�
bool UserTable::deleteUser(int fid)
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ����¼
    return this->deleteRecord();
}

// �����û���Ϣ
bool UserTable::updateUser(int fid, const QString& userName, const QString& fullName, const QString& password, int level)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        record.setValue(F_USERNAME, userName);
        record.setValue(F_FULLNAME, fullName);
        record.setValue(F_PASSWORD, password);
        record.setValue(F_USERLEVEL, level);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}