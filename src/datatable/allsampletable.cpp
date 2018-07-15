#include <QtDebug>

#include "field.h"
#include "paras.h"
#include "database.h"
#include "allsampletable.h"


AllSampleTable::AllSampleTable()
    : SampleTable("T_ALLSAMPLE")
{

}

AllSampleTable::~AllSampleTable()
{

}

// �������
bool AllSampleTable::addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult)
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
        this->setSampleInfo(record, sampleInfo);
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

// ��������
bool AllSampleTable::updateSample(int fid, const SampleInfo& sampleInfo)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
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

bool AllSampleTable::updateSample(int fid, const ParaList& paraResult)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        this->setParaResult(record, paraResult);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}

bool AllSampleTable::updateSample(int fid, const ParaList& lowLimits, const ParaList& highLimits)
{
    bool ret = false;

    // ��ѯ����������¼��ֻӦ�ò�ѯ��1����¼��
    QSqlQuery query = this->selectRecord(fid);
    if (query.next())
    {
        // ������Ҫ���µ��ֶ�
        QSqlRecord record = query.record();

        this->setLowLimit(record, lowLimits);
        this->setHighLimit(record, highLimits);

        // ִ�ж�ӦSQL����
        ret = this->updateRecord(record);
    }

    return ret;
}

bool AllSampleTable::updateSample(int fid, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist)
{
    QSqlQuery query(Database::database());
    QString sql = QString("UPDATE %1 SET %2 = ?, %3 = ?, %4 = ?, %5 = ?, %6 = ?, %7 = ? WHERE %8 = %9").arg(this->tableName()).
                  arg(F_WBC_HIST).arg(F_WBC_LINE).arg(F_RBC_HIST).arg(F_RBC_LINE).arg(F_PLT_HIST).arg(F_PLT_LINE).arg(F_ID).arg(fid);

    query.prepare(sql);

    // WBCֱ��ͼ����
    {
        // ֱ��ͼ
        QByteArray histByteArray;
        histByteArray.reserve(wbcHist.dataLen);

        for (int i = 0; i < wbcHist.dataLen; i++)
        {
            histByteArray.append(wbcHist.datas[i]);
        }

        query.addBindValue(histByteArray);

        // ������
        QByteArray lineByteArray;
        lineByteArray.reserve(wbcHist.lineLen);

        for (int i = 0; i < wbcHist.lineLen; i++)
        {
            lineByteArray.append(wbcHist.lines[i]);
        }

        query.addBindValue(lineByteArray);
    }

    // RBCֱ��ͼ����
    {
        // ֱ��ͼ
        QByteArray histByteArray;
        histByteArray.reserve(rbcHist.dataLen);

        for (int i = 0; i < rbcHist.dataLen; i++)
        {
            histByteArray.append(rbcHist.datas[i]);
        }

        query.addBindValue(histByteArray);

        // ������
        QByteArray lineByteArray;
        lineByteArray.reserve(rbcHist.lineLen);

        for (int i = 0; i < rbcHist.lineLen; i++)
        {
            lineByteArray.append(rbcHist.lines[i]);
        }

        query.addBindValue(lineByteArray);
    }

    // PLTֱ��ͼ����
    {
        // ֱ��ͼ
        QByteArray histByteArray;
        histByteArray.reserve(pltHist.dataLen);

        for (int i = 0; i < pltHist.dataLen; i++)
        {
            histByteArray.append(pltHist.datas[i]);
        }

        query.addBindValue(histByteArray);

        // ������
        QByteArray lineByteArray;
        lineByteArray.reserve(pltHist.lineLen);

        for (int i = 0; i < pltHist.lineLen; i++)
        {
            lineByteArray.append(pltHist.lines[i]);
        }

        query.addBindValue(lineByteArray);
    }

    return query.exec();
}