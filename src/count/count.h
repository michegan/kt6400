#ifndef _COUNT_H_
#define _COUNT_H_


#include <QObject>

#include "para.h"
#include "histinfo.h"
#include "libcount.h"
#include "sampleinfo.h"

class CountPrivate;


// 计数
class COUNT_EXPORT Count : public QObject
{
    Q_OBJECT

public:
    Count();
    virtual ~Count();

    // 启动计数
    int startCount(const SampleInfo& sampleInfo, float* countTime = 0);

    // 算法结果
    HistInfo wbcHist() const;
    HistInfo rbcHist() const;
    HistInfo pltHist() const;

    ParaList paraResult() const;

signals:
    // 算法结束
    void algFinished();

    // 计数结束
    void countFinished(bool result);

private slots:
    // 算法结束
    void onAlgFinished();

    // 数据采集结束
    void onDmaDataReady();

    // 时序结束
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    CountPrivate* d;
};


#endif // _COUNT_H_