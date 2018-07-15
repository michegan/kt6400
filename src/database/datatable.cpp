#include <QtDebug>
#include <QStringList>

#include "database.h"
#include "datatable.h"


class DataTablePrivate
{
public:
    DataTablePrivate();
    ~DataTablePrivate();

    // 格式化
    QString format(const QString& value);

public:
    // 表明
    QString table;

    // 条件
    QString condition;

    // 选中记录（界面用）
    QList<int> selectedRecords;
};

DataTablePrivate::DataTablePrivate()
    : table(""), condition("")
{

}

DataTablePrivate::~DataTablePrivate()
{

}

// 格式化
QString DataTablePrivate::format(const QString& value)
{
    return "\"" + value + "\"";
}


DataTable::DataTable(const QString& table)
    : QObject(), d(new DataTablePrivate())
{
    d->table = table;
}

DataTable::~DataTable()
{

}

// 表名
QString DataTable::tableName() const
{
    return d->table;
}

//
// 表信息
// 

// 数据记录
QSqlRecord DataTable::record() const
{
    return Database::record(d->table);
}

//
// 条件
//

// 清空条件
void DataTable::clearConditions()
{
    d->condition.clear();
}

// 添加AND条件
void DataTable::addAndCondition(const QString& field, const QVariant& condition, bool equal)
{
    QString scondition;

    // 前缀
    if (!d->condition.isEmpty())
    {
        scondition += " AND ";
    }

    // 条件字段
    scondition += d->format(field);

    // 条件值
    scondition += (equal ? " = " : " != ");
    scondition += d->format(condition.toString());

    // 追加上述条件
    d->condition += scondition;
}

// 添加OR条件
void DataTable::addOrCondition(const QString& field, const QVariant& condition, bool equal)
{
    QString scondition;

    // 前缀
    if (!d->condition.isEmpty())
    {
        scondition += " OR ";
    }

    // 条件字段
    scondition += d->format(field);

    // 条件值
    scondition += (equal ? " = " : " != ");
    scondition += d->format(condition.toString());

    // 追加上述条件
    d->condition += scondition;
}

// 添加WHERE符合条件
void DataTable::addWhereCondition(const QString& condition)
{
    if (d->condition.isEmpty())
    {
        d->condition += condition;
    }
    else
    {
        d->condition += " AND " + condition;
    }
}

//
// 数据库操作
//

// 下一F_ID
int DataTable::nextFid()
{
    int fid = -1;

    // 查询当前最大FID
    QString sql = QString("select MAX(%1) from %2").arg(F_ID).arg(d->table);

    QSqlQuery query = Database::selectRecord(sql);
    if (query.next())
    {
        // 提取所需要的字段
        QSqlRecord record = query.record();

        // 解决如下运行BUG
        // [INFO T1075470336] 3-3 15:8:22 871 Database executeNonQuery "INSERT INTO T_ALLSAMPLE ("F_ID", "F_SID", "F_WORKMODE", "F_SAMPLEMODE", "F_SPECIESMODE", "F_BLOODMODE", "F_ANALYSISMODE", "F_PREPROCESSMODE", "F_SENDER", "F_SEND_TIME", "F_TESTER", "F_TEST_TIME
        // [INFO T1075470336] 3-3 15:8:22 895 Database executeNonQuery false "PRIMARY KEY must be unique Unable to fetch row" 
        // [WARNING T1075470336] 3-3 15:8:22 898 Count onDmaDataReady addSample fail 
        fid = record.value(0).toInt();
    }

    return (fid + 1);
}

// 新增
bool DataTable::insertRecord(const QSqlRecord& record)
{
    bool ret = Database::insertRecord(d->table, record);
    if (ret)
    {
        emit dataChanged();
    }
    return ret;
}

// 删除
bool DataTable::deleteRecord()
{
    bool ret = Database::deleteRecord(d->table, d->condition);
    if (ret)
    {
        emit dataChanged();
    }
    return ret;
}

bool DataTable::deleteRecord(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除
    return this->deleteRecord();
}

bool DataTable::deleteSelectdRecords()
{
    bool ret = true;

    // 从数据库中删除样本
    this->beginTransaction();

    QList<int> selectSamples = this->selectedRecords();
    foreach (int fid, selectSamples)
    {
        if (!this->deleteRecord(fid))
        {
            ret = false;
            break;
        }
    }

    if (ret)
    {
        // 删除成功，提交事务
        this->commitTransaction();

        // 清空选中样本
        this->clearSelectedRecords();
    }
    else
    {
        // 删除失败，回滚事务
        this->rollbackTransaction();
    }

    return ret;
}

// 更新
bool DataTable::updateRecord(const QSqlRecord& record)
{
    bool ret = Database::updateRecord(d->table, record, d->condition);
    if (ret)
    {
        emit dataChanged();
    }
    return ret;
}

// 记录数
int DataTable::numOfRecords()
{
    return Database::numOfRecords(d->table, d->condition);
}

// 查询
QSqlQuery DataTable::selectRecord()
{
    return this->selectRecord(this->record());
}

QSqlQuery DataTable::selectRecord(int fid)
{
    // 查询条件
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // 删除
    return this->selectRecord();
}

QSqlQuery DataTable::selectRecord(const QSqlRecord& record)
{
    QSqlQuery sqlQuery = Database::selectRecord(d->table, record, d->condition);
    return sqlQuery;
}

//
// 选中记录（界面用）
//
void DataTable::clearSelectedRecords()
{
    d->selectedRecords.clear();

    // 选中记录变化（界面用）
    emit selectedRecordsChanged(d->selectedRecords);
}

QList<int> DataTable::selectedRecords() const
{
    return d->selectedRecords;
}

void DataTable::selectedRecord(int fid, bool select)
{
    if (select)
    {
        // 选中样本
        if (!d->selectedRecords.contains(fid))
        {
            d->selectedRecords.append(fid);

            // 选中记录变化（界面用）
            emit selectedRecordsChanged(d->selectedRecords);
        }
    }
    else
    {
        // 剔除样本
        if (d->selectedRecords.contains(fid))
        {
            d->selectedRecords.removeOne(fid);

            // 选中记录变化（界面用）
            emit selectedRecordsChanged(d->selectedRecords);
        }
    }
}

//
// 事务处理
//

// 开始事务
bool DataTable::beginTransaction()
{
    return Database::beginTransaction();
}

// 提交事务
bool DataTable::commitTransaction()
{
    return Database::commitTransaction();
}

// 事务回滚
bool DataTable::rollbackTransaction()
{
    return Database::rollbackTransaction();
}