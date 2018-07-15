#ifndef _SAMPLE_TABLE_H_
#define _SAMPLE_TABLE_H_


#include "para.h"
#include "histinfo.h"
#include "ljqcinfo.h"
#include "datatable.h"
#include "sampleinfo.h"
#include "libdatatable.h"


// ����������ݱ�
class DATATABLE_EXPORT SampleTable : public DataTable
{
public:
    SampleTable(const QString& table);
    virtual ~SampleTable();

public:
    // ��������
    QString paraFieldName(const QString& para);

    // �ʿ���Ϣ
    void getLJQcInfo(LJQcInfo& qcInfo, const QSqlRecord& record);
    void setLJQcInfo(QSqlRecord& record, const LJQcInfo& qcInfo);

    // ������Ϣ
    void getSampleInfo(SampleInfo& sampleInfo, const QSqlRecord& record);
    void setSampleInfo(QSqlRecord& record, const SampleInfo& sampleInfo);
    
    // �������
    void getParaResult(ParaList& paraResult, const QSqlRecord& record);
    void setParaResult(QSqlRecord& record, const ParaList& paraResult);

    // �ο���Χ����
    void getLowLimit(ParaList& lowLimits, const QSqlRecord& record);
    void setLowLimit(QSqlRecord& record, const ParaList& lowLimits);

    // �ο���Χ����
    void getHighLimit(ParaList& highLimits, const QSqlRecord& record);
    void setHighLimit(QSqlRecord& record, const ParaList& highLimits);

    // ֱ��ͼ����
    void getHistInfo(HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist, const QSqlRecord& record);
};


#endif // _SAMPLE_TABLE_H_