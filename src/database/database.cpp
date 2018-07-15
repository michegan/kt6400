#include <QHash>
#include <QtDebug>
#include <QSqlError>
#include <QSqlDriver>

#include "database.h"


// 数据库
namespace Database
{
    // 数据库
    static QSqlDatabase s_sqlDatabase;

    // SQL执行
    bool executeNonQuery(const QString& sql)
    {
        // SQL执行
        QSqlQuery sqlQuery(s_sqlDatabase);
        bool result = sqlQuery.exec(sql);

        qDebug() << "Database executeNonQuery" << result << sqlQuery.lastError().text();

        return result;
    }

    // SQL语法
    QString sqlStatement(QSqlDriver::StatementType type, const QString& table, const QSqlRecord& record, bool preparedStatement)
    {
        // 数据引擎
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->sqlStatement(type, table, record, preparedStatement) : "");
    }

    // 数据库
    QSqlDatabase database()
    {
        return s_sqlDatabase;
    }

    // 打开数据库
    bool open(const QString& database)
    {
        return Database::open(database, "", "");
    }

    bool open(const QString& database, const QString& user, const QString& password)
    {
        qDebug() << "Database open";

        // 关闭数据库，避免重复打开失败
        Database::close();

        // 先移除数据库
        QSqlDatabase::removeDatabase(database);

        // 再重新添加数据库
        s_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE", database);
        if (s_sqlDatabase.isValid())
        {
            s_sqlDatabase.setDatabaseName(database);
        }
        else
        {
            qWarning() << "Database open addDatabase fail";
        }

        // 打开数据库
        return s_sqlDatabase.open(user, password);
    }

    // 关闭数据库
    bool close()
    {
        qDebug() << "Database close";

        // 关闭数据库
        if (s_sqlDatabase.isOpen())
        {
            s_sqlDatabase.close();
        }

        return true;
    }

    // 表信息
    QStringList tables()
    {
        return (s_sqlDatabase.isOpen() ? s_sqlDatabase.tables() : QStringList());
    }

    QSqlRecord record(const QString& table)
    {
        return (s_sqlDatabase.isOpen() ? s_sqlDatabase.record(table) : QSqlRecord());
    }

    // 数据操作
    bool insertRecord(const QString& table, const QSqlRecord& record)
    {
        // SQL语句
        QString sql = Database::sqlStatement(QSqlDriver::InsertStatement, table, record, false);

        // SQL执行
        return Database::executeNonQuery(sql);
    }

    // 删除
    bool deleteRecord(const QString& table, const QString& where)
    {
        QSqlRecord record = Database::record(table);

        // SQL语句
        QString sql = Database::sqlStatement(QSqlDriver::DeleteStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQL执行
        return Database::executeNonQuery(sql);
    }

    // 更新
    bool updateRecord(const QString& table, const QSqlRecord& record, const QString& where)
    {
        // SQL语句
        QString sql = Database::sqlStatement(QSqlDriver::UpdateStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQL执行
        return Database::executeNonQuery(sql);
    }

    // 查询
    QSqlQuery selectRecord(const QString& sql)
    {
        // SQL执行
        QSqlQuery query = s_sqlDatabase.exec(sql);
        qDebug() << "Database selectRecord" << query.lastError().text();

        return query;
    }

    QSqlQuery selectRecord(const QString& table, const QSqlRecord& record, const QString& where)
    {
        // SQL语句
        QString sql = Database::sqlStatement(QSqlDriver::SelectStatement, table, record, false);
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQL执行
        QSqlQuery query = s_sqlDatabase.exec(sql);
        qDebug() << "Database selectRecord" << query.lastError().text();

        return query;
    }

    // 记录数
    int numOfRecords(const QString& table, const QString& where)
    {
        int count = -1;

        // SQL语句
        QString sql = "SELECT COUNT(*) FROM " + table;
        if (!where.isEmpty())
        {
            sql += " WHERE " + where;
        }

        // SQL执行
        QSqlQuery query = s_sqlDatabase.exec(sql);

        // 只有一条记录
        if (query.next())
        {
            // 当前记录值
            QSqlRecord record = query.record();
            count = record.value("COUNT(*)").toInt();
        }

        return count;
    }

    // 开始事务
    bool beginTransaction()
    {
        qDebug() << "Database beginTransaction";

        // 数据引擎
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->beginTransaction() : false);
    }

    // 提交事务
    bool commitTransaction()
    {
        qDebug() << "Database commitTransaction";

        // 数据引擎
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->commitTransaction() : false);
    }

    // 事务回滚
    bool rollbackTransaction()
    {
        qDebug() << "Database rollbackTransaction";

        // 数据引擎
        QSqlDriver* sqlDriver = s_sqlDatabase.driver();
        return (sqlDriver ? sqlDriver->rollbackTransaction() : false);
    }

    // 执行SQL语句
    bool executeSQL(const QString& strSQL)
    {
        return Database::executeNonQuery(strSQL);
    }
}