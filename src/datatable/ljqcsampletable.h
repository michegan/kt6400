#ifndef _LJ_QC_SAMPLE_TABLE_H_
#define _LJ_QC_SAMPLE_TABLE_H_


#include "sampletable.h"


// LJ�ʿ��������ݱ�
class DATATABLE_EXPORT LJQcSampleTable : public SampleTable
{
public:
    LJQcSampleTable(int fileNo);
    virtual ~LJQcSampleTable();

    // ��¼��
    int numOfRecords();

    // ȫ������
    QList<int> allSamples();

    // ��ȡ����
    bool getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult);

    // �������
    bool addSample(int& fid, const QDateTime& testTime, const ParaList& paraResult);

    // ɾ������
    bool deleteAllSamples();
    bool deleteSelectSamples();

private:
    // �ļ���
    int fileNo;
};


#endif // _LJ_QC_SAMPLE_TABLE_H_