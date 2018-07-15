#ifndef _REF_RANGE_H_
#define _REF_RANGE_H_


#include "para.h"
#include "libcount.h"
#include "sampleinfo.h"


// �ο���Χ
namespace RefRange
{
    // ��ȡ�ο���Χ
    COUNT_EXPORT bool getLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits);
};


#endif // _REF_RANGE_H_