#ifndef _COUNT_H_
#define _COUNT_H_


#include <QObject>

#include "para.h"
#include "histinfo.h"
#include "libcount.h"
#include "sampleinfo.h"

class CountPrivate;


// ����
class COUNT_EXPORT Count : public QObject
{
    Q_OBJECT

public:
    Count();
    virtual ~Count();

    // ��������
    int startCount(const SampleInfo& sampleInfo, float* countTime = 0);

    // �㷨���
    HistInfo wbcHist() const;
    HistInfo rbcHist() const;
    HistInfo pltHist() const;

    ParaList paraResult() const;

signals:
    // �㷨����
    void algFinished();

    // ��������
    void countFinished(bool result);

private slots:
    // �㷨����
    void onAlgFinished();

    // ���ݲɼ�����
    void onDmaDataReady();

    // ʱ�����
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    CountPrivate* d;
};


#endif // _COUNT_H_