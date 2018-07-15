#ifndef _REVIEW_SAMPLE_TABLE_H_
#define _REVIEW_SAMPLE_TABLE_H_


#include "allsampletable.h"

class ReviewSampleTablePrivate;


// ��Ч��ʶ
#define INVALID_FID         (-1)
// ��Ч����
#define INVALID_INDEX       (-1)


// �����������ݱ�
class ReviewSampleTable : public AllSampleTable
{
    Q_OBJECT

public:
    ReviewSampleTable();
    virtual ~ReviewSampleTable();

    // ��ǰ����
    int currentIndex() const;
    void setCurrentIndex(int index);

    // ȫ������
    QList<int> allSamples() const;

    // ��ȡ����
    int fid(int index) const;

    // ��ѯ
    virtual bool selectSamples();

    // ��ȡ����
    virtual bool getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult);
    virtual bool getSample(int fid, HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist);

    // �������
    virtual bool addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult);

    // ɾ������
    bool deleteAllSamples();
    bool deleteCurrentSample();
    bool deleteSelectSamples();

signals:
    // ��ǰ�����仯
    void currentSampleChanged(int index, const QList<int>& fids);

public:
    // ����
    static void createInstance();
    static ReviewSampleTable* instance();

private:
    ReviewSampleTablePrivate* d;
};


#endif // _REVIEW_SAMPLE_TABLE_H_