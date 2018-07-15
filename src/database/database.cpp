#include <QHash>
#include <QtDebug>
#include <QSqlError>
#include <QSqlDriver>

#include "database.h"


// ���ݿ�
namespace Database
{
    // ���ݿ�
    static QSqlDatabase s_sqlDatabase;

    // SQLִ��
    bool executeNonQuery(const QString& sql)
    {
        // SQLִ��
        QSqlQuery sqlQuery(s_sqlDatabase);
        bool result = sqlQuery.exec(sql);

        qDebug() << "Database executeNonQuery" << result << sqlQuery.lastError().text();

        return result;
    }

    // SQL�﷨
    QString sqlStatement(QSqlDriver::StatementType type, const QString& table, const QSqlRecord& record, bool preparedStatement)
    {
        // ��������
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->sqlStatement(type, table, record, preparedStatement) : "");
    }

    // ���ݿ�
    QSqlDatabase database()
    {
        return s_sqlDatabase;
    }

    // �����ݿ�
    bool open(const QString& database)
    {
        return Database::open(database, "", "");
    }

    bool open(const QString& database, const QString& user, const QString& password)
    {
        qDebug() << "Database open";

        // �ر����ݿ⣬�����ظ���ʧ��
        Database::close();

        // ���Ƴ����ݿ�
        QSqlDatabase::removeDatabase(database);

        // ������������ݿ�
        s_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE", database);
        if (s_sqlDatabase.isValid())
        {
            s_sqlDatabase.setDatabaseName(database);
        }
        else
        {
            qWarning() << "Database open addDatabase fail";
        }

        // �����ݿ�
        return s_sqlDatabase.open(user, password);
    }

    // �ر����ݿ�
    bool close()
    {
        qDebug() << "Database close";

        // �ر����ݿ�
        if (s_sqlDatabase.isOpen())
        {
            s_sqlDatabase.close();
        }

        return true;
    }

    // ����Ϣ
    QStringList tables()
    {
        return (s_sqlDatabase.isOpen() ? s_sqlDatabase.tables() : QStringList());
    }

    QSqlRecord record(const QString& table)
    {
        return (s_sqlDatabase.isOpen() ? s_sqlDatabase.record(table) : QSqlRecord());
    }

    // ���ݲ���
    bool insertRecord(const QString& table, const QSqlRecord& record)
    {
        // SQL���
        QString sql = Database::sqlStatement(QSqlDriver::InsertStatement, table, record, false);

        // SQLִ��
        return Database::executeNonQuery(sql);
    }

    // ɾ��
    bool deleteRecord(const QString& table, const QString& where)
    {
        QSqlRecord record = Database::record(table);

        // SQL���
        QString sql = Database::sqlStatement(QSqlDriver::DeleteStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQLִ��
        return Database::executeNonQuery(sql);
    }

    // ����
    bool updateRecord(const QString& table, const QSqlRecord& record, const QString& where)
    {
        // SQL���
        QString sql = Database::sqlStatement(QSqlDriver::UpdateStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQLִ��
        return Database::executeNonQuery(sql);
    }

    // ��ѯ
    QSqlQuery selectRecord(const QString& sql)
    {
        // SQLִ��
        QSqlQuery query = s_sqlDatabase.exec(sql);
        qDebug() << "Database selectRecord" << query.lastError().text();

        return query;
    }

    QSqlQuery selectRecord(const QString& table, const QSqlRecord& record, const QString& where)
    {
        // SQL���
        QString sql = Database::sqlStatement(QSqlDriver::SelectStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQLִ��
        QSqlQuery query = s_sqlDatabase.exec(sql);
        qDebug() << "Database selectRecord" << query.lastError().text();

        return query;
    }

    // ��¼��
    int numOfRecords(const QString& table, const QString& where)
    {
        int count = -1;

        // SQL���
        QString sql = "SELECT COUNT(*) FROM " + table;
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQLִ��
        QSqlQuery query = s_sqlDatabase.exec(sql);

        // ֻ��һ����¼
        if (query.next())
        {
            // ��ǰ��¼ֵ
            QSqlRecord record = query.record();
            count = record.value("COUNT(*)").toInt();
        }

        return count;
    }

    // ��ʼ����
    bool beginTransaction()
    {
        qDebug() << "Database beginTransaction";

        // ��������
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->beginTransaction() : false);
    }

    // �ύ����
    bool commitTransaction()
    {
        qDebug() << "Database commitTransaction";

        // ��������
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->commitTransaction() : false);
    }

    // ����ع�
    bool rollbackTransaction()
    {
        qDebug() << "Database rollbackTransaction";

        // ��������
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->rollbackTransaction() : false);
    }

    // ִ��SQL���
    bool executeSQL(const QString& strSQL)
    {
        return Database::executeNonQuery(strSQL);
    }
}