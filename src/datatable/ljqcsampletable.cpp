#include <QtDebug>

#include "field.h"
#include "paras.h"
#include "ljqcsampletable.h"


LJQcSampleTable::LJQcSampleTable(int fileNo)
    : SampleTable("T_LJQCSAMPLE")
{
    this->fileNo = fileNo;
}

LJQcSampleTable::~LJQcSampleTable()
{

}

// ��¼��
int LJQcSampleTable::numOfRecords()
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // ��¼��
    return SampleTable::numOfRecords();
}

// ȫ������
QList<int> LJQcSampleTable::allSamples()
{
    // ȫ������
    QList<int> allSamples;

    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // ����ȫ��������Ϣ
    QSqlQuery sqlQuery = this->selectRecord();
    while (sqlQuery.next())
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = sqlQuery.record();

        // �û���Ϣ
        int fid = record.value(F_SID).toInt();
        allSamples.append(fid);
    }

    return allSamples;
}

// ��ȡ����
bool LJQcSampleTable::getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult)
{
    // ��ѯ�������Ч������
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = query.record();

        // ������Ϣ
        this->getSampleInfo(sampleInfo, record);
        // �������
        this->getParaResult(paraResult, record);
    }

    return ret;
}

// �������
bool LJQcSampleTable::addSample(int& fid, const QDateTime& testTime, const ParaList& paraResult)
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
        record.setValue(F_FILENO, this->fileNo);
        record.setValue(F_TEST_TIME, testTime);
        this->setParaResult(record, paraResult);

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
bool LJQcSampleTable::deleteAllSamples()
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_FILENO, this->fileNo);

    // ɾ����¼
    return this->deleteRecord();
}

bool LJQcSampleTable::deleteSelectSamples()
{
    return this->deleteSelectdRecords();
}