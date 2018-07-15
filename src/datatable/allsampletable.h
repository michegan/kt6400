#ifndef _ALL_SAMPLE_TABLE_H_
#define _ALL_SAMPLE_TABLE_H_


#include "sampletable.h"


// �����������ݱ�
class DATATABLE_EXPORT AllSampleTable : public SampleTable
{
public:
    AllSampleTable();
    virtual ~AllSampleTable();

    // �������
    virtual bool addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult);

    // ��������
    virtual bool updateSample(int fid, const SampleInfo& sampleInfo);
    virtual bool updateSample(int fid, const ParaList& paraResult);
    virtual bool updateSample(int fid, const ParaList& lowLimits, const ParaList& highLimits);
    virtual bool updateSample(int fid, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);
};


#endif // _ALL_SAMPLE_TABLE_H_