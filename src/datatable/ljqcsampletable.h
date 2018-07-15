#ifndef _LJ_QC_SAMPLE_TABLE_H_
#define _LJ_QC_SAMPLE_TABLE_H_


#include "sampletable.h"


// LJ质控样本数据表
class DATATABLE_EXPORT LJQcSampleTable : public SampleTable
{
public:
    LJQcSampleTable(int fileNo);
    virtual ~LJQcSampleTable();

    // 记录数
    int numOfRecords();

    // 全部样本
    QList<int> allSamples();

    // 获取样本
    bool getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult);

    // 添加样本
    bool addSample(int& fid, const QDateTime& testTime, const ParaList& paraResult);

    // 删除样本
    bool deleteAllSamples();
    bool deleteSelectSamples();

private:
    // 文件号
    int fileNo;
};


#endif // _LJ_QC_SAMPLE_TABLE_H_