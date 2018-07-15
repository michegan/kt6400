#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "libdatabase.h"


// ���ݿ�
namespace Database
{
    // ���ݿ�
    DATABASE_EXPORT QSqlDatabase database();

    // �����ݿ�
    DATABASE_EXPORT bool open(const QString& database);
    DATABASE_EXPORT bool open(const QString& database, const QString& user, const QString& password);

    // �ر����ݿ�
    DATABASE_EXPORT bool close();

    // ����Ϣ
    DATABASE_EXPORT QStringList tables();
    DATABASE_EXPORT QSqlRecord record(const QString& table);

    // ����
    DATABASE_EXPORT bool insertRecord(const QString& table, const QSqlRecord& record);

    // ɾ��
    DATABASE_EXPORT bool deleteRecord(const QString& table, const QString& where);

    // ����
    DATABASE_EXPORT bool updateRecord(const QString& table, const QSqlRecord& record, const QString& where);

    // ��ѯ
    DATABASE_EXPORT QSqlQuery selectRecord(const QString& sql);
    DATABASE_EXPORT QSqlQuery selectRecord(const QString& table, const QSqlRecord& record, const QString& where);

    // ��¼��
    DATABASE_EXPORT int numOfRecords(const QString& table, const QString& where);

    // ��ʼ����
    DATABASE_EXPORT bool beginTransaction();

    // �ύ����
    DATABASE_EXPORT bool commitTransaction();

    // ����ع�
    DATABASE_EXPORT bool rollbackTransaction();

    // ִ��SQL���
    DATABASE_EXPORT bool executeSQL(const QString& strSQL);
};


#endif // _DATABASE_H_