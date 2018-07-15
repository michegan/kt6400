#ifndef _NEXT_SAMPLE_TABLE_H_
#define _NEXT_SAMPLE_TABLE_H_


#include "sampletable.h"


// ��һ�������ݱ�
class DATATABLE_EXPORT NextSampleTable : public SampleTable
{
public:
    NextSampleTable();
    virtual ~NextSampleTable();

    // ��ȡ��һ������Ϣ
    bool nextSampleInfo(SampleInfo& sampleInfo);

    // ������һ������Ϣ
    bool setNextSampleInfo(const SampleInfo& sampleInfo);
};


#endif // _NEXT_SAMPLE_TABLE_H_