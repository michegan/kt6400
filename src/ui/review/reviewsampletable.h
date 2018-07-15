#ifndef _REVIEW_SAMPLE_TABLE_H_
#define _REVIEW_SAMPLE_TABLE_H_


#include "allsampletable.h"

class ReviewSampleTablePrivate;


// 无效标识
#define INVALID_FID         (-1)
// 无效索引
#define INVALID_INDEX       (-1)


// 所有样本数据表
class ReviewSampleTable : public AllSampleTable
{
    Q_OBJECT

public:
    ReviewSampleTable();
    virtual ~ReviewSampleTable();

    // 当前样本
    int currentIndex() const;
    void setCurrentIndex(int index);

    // 全部样本
    QList<int> allSamples() const;

    // 获取样本
    int fid(int index) const;

    // 查询
    virtual bool selectSamples();

    // 获取样本
    virtual bool getSample(int fid, SampleInfo& sampleInfo, ParaList& paraResult);
    virtual bool getSample(int fid, HistInfo& wbcHist, HistInfo& rbcHist, HistInfo& pltHist);

    // 添加样本
    virtual bool addSample(int& fid, const SampleInfo& sampleInfo, const ParaList& paraResult);

    // 删除样本
    bool deleteAllSamples();
    bool deleteCurrentSample();
    bool deleteSelectSamples();

signals:
    // 当前样本变化
    void currentSampleChanged(int index, const QList<int>& fids);

public:
    // 单键
    static void createInstance();
    static ReviewSampleTable* instance();

private:
    ReviewSampleTablePrivate* d;
};


#endif // _REVIEW_SAMPLE_TABLE_H_