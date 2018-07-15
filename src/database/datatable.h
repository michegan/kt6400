#ifndef _DATA_TABLE_H_
#define _DATA_TABLE_H_


#include <QHash>
#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>

#include "libdatabase.h"

class DataTablePrivate;


// 字段定义
#define F_ID                            "F_ID"


// 数据表
class DATABASE_EXPORT DataTable : public QObject
{
    Q_OBJECT

public:
    DataTable(const QString& table);
    virtual ~DataTable();

    // 表名
    QString tableName() const;

    //
    // 表信息
    // 

    // 数据记录
    QSqlRecord record() const;

    //
    // 条件
    //

    // 清空条件
    void clearConditions();
    // 添加AND条件
    void addAndCondition(const QString& field, const QVariant& condition, bool equal = true);
    // 添加OR条件
    void addOrCondition(const QString& field, const QVariant& condition, bool equal = true);
    // 添加WHERE符合条件
    void addWhereCondition(const QString& condition);

    //
    // 数据库操作
    //

    // 下一F_ID
    int nextFid();

    // 新增
    bool insertRecord(const QSqlRecord& record);

    // 删除
    bool deleteRecord();
    bool deleteRecord(int fid);
    bool deleteSelectdRecords();

    // 更新
    bool updateRecord(const QSqlRecord& record);

    // 记录数
    int numOfRecords();

    // 查询
    QSqlQuery selectRecord();
    QSqlQuery selectRecord(int fid);
    QSqlQuery selectRecord(const QSqlRecord& record);

    //
    // 选中记录（界面用）
    //
    void clearSelectedRecords();
    QList<int> selectedRecords() const;
    void selectedRecord(int fid, bool select);

    //
    // 事务处理
    //

    // 开始事务
    bool beginTransaction();

    // 提交事务
    bool commitTransaction();

    // 事务回滚
    bool rollbackTransaction();

signals:
    // 数据变化
    void dataChanged();

    // 选中记录变化（界面用）
    void selectedRecordsChanged(const QList<int>& fids);

private:
    DataTablePrivate* d;
};


#endif // _DATA_TABLE_H_