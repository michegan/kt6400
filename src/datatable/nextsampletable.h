#ifndef _NEXT_SAMPLE_TABLE_H_
#define _NEXT_SAMPLE_TABLE_H_


#include "sampletable.h"


// 下一样本数据表
class DATATABLE_EXPORT NextSampleTable : public SampleTable
{
public:
    NextSampleTable();
    virtual ~NextSampleTable();

    // 获取下一样本信息
    bool nextSampleInfo(SampleInfo& sampleInfo);

    // 更新下一样本信息
    bool setNextSampleInfo(const SampleInfo& sampleInfo);
};


#endif // _NEXT_SAMPLE_TABLE_H_