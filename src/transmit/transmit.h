#ifndef _TRANSMIT_H_
#define _TRANSMIT_H_


#include "para.h"
#include "histinfo.h"
#include "sampleinfo.h"
#include "libtransmit.h"


// ͨ��
namespace  Transmit
{
    // ����ͨ��
    TRANSMIT_EXPORT bool sendSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const HistInfo& wbcHist, const HistInfo& rbcHist, const HistInfo& pltHist);
};


#endif // _TRANSMITER_H_