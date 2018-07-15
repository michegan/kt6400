#ifndef _SAMPLE_TABLE_H_
#define _SAMPLE_TABLE_H_


#include "para.h"
#include "histinfo.h"
#include "ljqcinfo.h"
#include "datatable.h"
#include "sampleinfo.h"
#include "libdatatable.h"


// 样本相关数据表
class DATATABLE_EXPORT SampleTable : public DataTable
{
public:
    SampleTable(const QString& table);
    virtual ~SampleTable();

public:
    // 参数列名
    QString paraFieldName(const QString& para);

    // 质控信息
    void getLJQcInfo(LJQcInfo& qcInfo, const QSqlRecord& record);
    void setLJQcInfo(QSqlRecord& record, const LJQcInfo& qcInfo);

    // 样本信息
    void getSampleInfo(SampleInfo& sampleInfo, const QSqlRecord& record);
    void setSampleInfo(QSqlRecord& record, const SampleInfo& sampleInfo);
    
    // 参数结果
    void getParaResult(ParaList& paraResult, const QSqlRecord& record);
    void setParaResult(QSqlRecord& record, const ParaList& paraResult);

    // 参考范围下限
    void getLowLimit(ParaList& lowLimits, const QSqlRecord& record);
    void setLowLimit(QSqlRecord& record, const ParaList& lowLimits);

    // 参考范围上限
    void getHighLimit(ParaList& highLimits, const QSqlRecord& record);
    void setHighLimit(QSqlRecord& record, const ParaList& highLimits);

    // 直方图数据
    void getHistInfo(HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist, const QSqlRecord& record);
};


#endif // _SAMPLE_TABLE_H_