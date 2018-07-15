#ifndef _PRINT_H_
#define _PRINT_H_


#include <QList>

#include "libprint.h"

class HistInfo;
class ParaList;
class CalFactor;
class SampleInfo;
class PrintPrivate;


// 打印
class PRINT_EXPORT Print
{
public:
    Print();
    virtual ~Print();

    // 打印样本
    bool printSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);

    // 打印校准系数
    bool printCalFactors(const QList<CalFactor>& peripheralCalFactors, const QList<CalFactor>& prediluentCalFactors, const QList<CalFactor>& wholeBloodCalFactors);

private:
    PrintPrivate* d;
};


#endif // _PRINTER_H_