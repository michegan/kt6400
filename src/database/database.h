#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "libdatabase.h"


// 数据库
namespace Database
{
    // 数据库
    DATABASE_EXPORT QSqlDatabase database();

    // 打开数据库
    DATABASE_EXPORT bool open(const QString& database);
    DATABASE_EXPORT bool open(const QString& database, const QString& user, const QString& password);

    // 关闭数据库
    DATABASE_EXPORT bool close();

    // 表信息
    DATABASE_EXPORT QStringList tables();
    DATABASE_EXPORT QSqlRecord record(const QString& table);

    // 新增
    DATABASE_EXPORT bool insertRecord(const QString& table, const QSqlRecord& record);

    // 删除
    DATABASE_EXPORT bool deleteRecord(const QString& table, const QString& where);

    // 更新
    DATABASE_EXPORT bool updateRecord(const QString& table, const QSqlRecord& record, const QString& where);

    // 查询
    DATABASE_EXPORT QSqlQuery selectRecord(const QString& sql);
    DATABASE_EXPORT QSqlQuery selectRecord(const QString& table, const QSqlRecord& record, const QString& where);

    // 记录数
    DATABASE_EXPORT int numOfRecords(const QString& table, const QString& where);

    // 开始事务
    DATABASE_EXPORT bool beginTransaction();

    // 提交事务
    DATABASE_EXPORT bool commitTransaction();

    // 事务回滚
    DATABASE_EXPORT bool rollbackTransaction();

    // 执行SQL语句
    DATABASE_EXPORT bool executeSQL(const QString& strSQL);
};


#endif // _DATABASE_H_