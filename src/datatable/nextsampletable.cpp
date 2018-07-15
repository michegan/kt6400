#include <QtDebug>

#include "field.h"
#include "nextsampletable.h"


// F_IDֵ
#define F_ID_V                      (1)


NextSampleTable::NextSampleTable()
    : SampleTable("T_NEXTSAMPLE")
{

}

NextSampleTable::~NextSampleTable()
{

}

// ��ȡ��һ������Ϣ
bool NextSampleTable::nextSampleInfo(SampleInfo& sampleInfo)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(F_ID_V);
    if (query.next())
    {
        // ��ȡ����Ҫ���ֶ�
        QSqlRecord record = query.record();
        this->getSampleInfo(sampleInfo, record);

        ret = true;
    }

    return ret;
}

// ������һ������Ϣ
bool NextSampleTable::setNextSampleInfo(const SampleInfo& sampleInfo)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(F_ID_V);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();
        this->setSampleInfo(record, sampleInfo);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}