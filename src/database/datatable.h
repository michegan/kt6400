#ifndef _DATA_TABLE_H_
#define _DATA_TABLE_H_


#include <QHash>
#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>

#include "libdatabase.h"

class DataTablePrivate;


// �ֶζ���
#define F_ID                            "F_ID"


// ���ݱ�
class DATABASE_EXPORT DataTable : public QObject
{
    Q_OBJECT

public:
    DataTable(const QString& table);
    virtual ~DataTable();

    // ����
    QString tableName() const;

    //
    // ����Ϣ
    // 

    // ���ݼ�¼
    QSqlRecord record() const;

    //
    // ����
    //

    // �������
    void clearConditions();
    // ���AND����
    void addAndCondition(const QString& field, const QVariant& condition, bool equal = true);
    // ���OR����
    void addOrCondition(const QString& field, const QVariant& condition, bool equal = true);
    // ���WHERE��������
    void addWhereCondition(const QString& condition);

    //
    // ���ݿ����
    //

    // ��һF_ID
    int nextFid();

    // ����
    bool insertRecord(const QSqlRecord& record);

    // ɾ��
    bool deleteRecord();
    bool deleteRecord(int fid);
    bool deleteSelectdRecords();

    // ����
    bool updateRecord(const QSqlRecord& record);

    // ��¼��
    int numOfRecords();

    // ��ѯ
    QSqlQuery selectRecord();
    QSqlQuery selectRecord(int fid);
    QSqlQuery selectRecord(const QSqlRecord& record);

    //
    // ѡ�м�¼�������ã�
    //
    void clearSelectedRecords();
    QList<int> selectedRecords() const;
    void selectedRecord(int fid, bool select);

    //
    // ������
    //

    // ��ʼ����
    bool beginTransaction();

    // �ύ����
    bool commitTransaction();

    // ����ع�
    bool rollbackTransaction();

signals:
    // ���ݱ仯
    void dataChanged();

    // ѡ�м�¼�仯�������ã�
    void selectedRecordsChanged(const QList<int>& fids);

private:
    DataTablePrivate* d;
};


#endif // _DATA_TABLE_H_