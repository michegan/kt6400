#include <QtDebug>
#include <QStringList>

#include "database.h"
#include "datatable.h"


class DataTablePrivate
{
public:
    DataTablePrivate();
    ~DataTablePrivate();

    // ��ʽ��
    QString format(const QString& value);

public:
    // ����
    QString table;

    // ����
    QString condition;

    // ѡ�м�¼�������ã�
    QList<int> selectedRecords;
};

DataTablePrivate::DataTablePrivate()
    : table(""), condition("")
{

}

DataTablePrivate::~DataTablePrivate()
{

}

// ��ʽ��
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

// ����
QString DataTable::tableName() const
{
    return d->table;
}

//
// ����Ϣ
// 

// ���ݼ�¼
QSqlRecord DataTable::record() const
{
    return Database::record(d->table);
}

//
// ����
//

// �������
void DataTable::clearConditions()
{
    d->condition.clear();
}

// ���AND����
void DataTable::addAndCondition(const QString& field, const QVariant& condition, bool equal)
{
    QString scondition;

    // ǰ׺
    if (!d->condition.isEmpty())
    {
        scondition += " AND ";
    }

    // �����ֶ�
    scondition += d->format(field);

    // ����ֵ
    scondition += (equal ? " = " : " != ");
    scondition += d->format(condition.toString());

    // ׷����������
    d->condition += scondition;
}

// ���OR����
void DataTable::addOrCondition(const QString& field, const QVariant& condition, bool equal)
{
    QString scondition;

    // ǰ׺
    if (!d->condition.isEmpty())
    {
        scondition += " OR ";
    }

    // �����ֶ�
    scondition += d->format(field);

    // ����ֵ
    scondition += (equal ? " = " : " != ");
    scondition += d->format(condition.toString());

    // ׷����������
    d->condition += scondition;
}

// ���WHERE��������
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
// ���ݿ����
//

// ��һF_ID
int DataTable::nextFid()
{
    int fid = -1;

    // ��ѯ��ǰ���FID
    QString sql = QString("select MAX(%1) from %2").arg(F_ID).arg(d->table);

    QSqlQuery query = Database::selectRecord(sql);
    if (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();

        // �����������BUG
        // [INFO T1075470336] 3-3 15:8:22 871 Database executeNonQuery "INSERT INTO T_ALLSAMPLE ("F_ID", "F_SID", "F_WORKMODE", "F_SAMPLEMODE", "F_SPECIESMODE", "F_BLOODMODE", "F_ANALYSISMODE", "F_PREPROCESSMODE", "F_SENDER", "F_SEND_TIME", "F_TESTER", "F_TEST_TIME
        // [INFO T1075470336] 3-3 15:8:22 895 Database executeNonQuery false "PRIMARY KEY must be unique Unable to fetch row" 
        // [WARNING T1075470336] 3-3 15:8:22 898 Count onDmaDataReady addSample fail 
        fid = record.value(0).toInt();
    }

    return (fid + 1);
}

// ����
bool DataTable::insertRecord(const QSqlRecord& record)
{
    bool ret = Database::insertRecord(d->table, record);
    if (ret)
    {
        emit dataChanged();
    }
    return ret;
}

// ɾ��
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
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ��
    return this->deleteRecord();
}

bool DataTable::deleteSelectdRecords()
{
    bool ret = true;

    // �����ݿ���ɾ������
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
        // ɾ���ɹ����ύ����
        this->commitTransaction();

        // ���ѡ������
        this->clearSelectedRecords();
    }
    else
    {
        // ɾ��ʧ�ܣ��ع�����
        this->rollbackTransaction();
    }

    return ret;
}

// ����
bool DataTable::updateRecord(const QSqlRecord& record)
{
    bool ret = Database::updateRecord(d->table, record, d->condition);
    if (ret)
    {
        emit dataChanged();
    }
    return ret;
}

// ��¼��
int DataTable::numOfRecords()
{
    return Database::numOfRecords(d->table, d->condition);
}

// ��ѯ
QSqlQuery DataTable::selectRecord()
{
    return this->selectRecord(this->record());
}

QSqlQuery DataTable::selectRecord(int fid)
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ��
    return this->selectRecord();
}

QSqlQuery DataTable::selectRecord(const QSqlRecord& record)
{
    QSqlQuery sqlQuery = Database::selectRecord(d->table, record, d->condition);
    return sqlQuery;
}

//
// ѡ�м�¼�������ã�
//
void DataTable::clearSelectedRecords()
{
    d->selectedRecords.clear();

    // ѡ�м�¼�仯�������ã�
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
        // ѡ������
        if (!d->selectedRecords.contains(fid))
        {
            d->selectedRecords.append(fid);

            // ѡ�м�¼�仯�������ã�
            emit selectedRecordsChanged(d->selectedRecords);
        }
    }
    else
    {
        // �޳�����
        if (d->selectedRecords.contains(fid))
        {
            d->selectedRecords.removeOne(fid);

            // ѡ�м�¼�仯�������ã�
            emit selectedRecordsChanged(d->selectedRecords);
        }
    }
}

//
// ������
//

// ��ʼ����
bool DataTable::beginTransaction()
{
    return Database::beginTransaction();
}

// �ύ����
bool DataTable::commitTransaction()
{
    return Database::commitTransaction();
}

// ����ع�
bool DataTable::rollbackTransaction()
{
    return Database::rollbackTransaction();
}