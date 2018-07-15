#include <QtDebug>

#include "field.h"
#include "ljqcfiletable.h"


LJQcFileTable::LJQcFileTable()
    : SampleTable("T_LJQCFILE")
{

}

LJQcFileTable::~LJQcFileTable()
{

}

// ��ȡ�ļ�
bool LJQcFileTable::getFile(int fid, LJQcInfo& qcInfo, ParaList& lowLimits, ParaList& highLimits)
{
    // ��ѯ�������Ч������
    QSqlQuery query = this->selectRecord(fid);

    bool ret = query.next();
    if (ret)
    {
        // ��ǰ��¼ֵ
        QSqlRecord record = query.record();

        // �ʿ���Ϣ
        this->getLJQcInfo(qcInfo, record);
        // �ο���Χ����
        this->getLowLimit(lowLimits, record);
        // �ο���Χ����
        this->getHighLimit(highLimits, record);
    }

    return ret;
}

// �����ļ�
bool LJQcFileTable::updateFile(int fid, const LJQcInfo& qcInfo, const ParaList& lowLimits, const ParaList& highLimits)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        this->setLJQcInfo(record, qcInfo);
        this->setLowLimit(record, lowLimits);
        this->setHighLimit(record, highLimits);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}

// ����ļ�
bool LJQcFileTable::clearFile(int fid)
{
    // ��ѯ����
    this->clearConditions();
    this->addAndCondition(F_ID, fid);

    // ɾ��
    return this->deleteRecord();
}