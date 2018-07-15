#ifndef _REF_RANGE_H_
#define _REF_RANGE_H_


#include "para.h"
#include "libcount.h"
#include "sampleinfo.h"


// 参考范围
namespace RefRange
{
    // 获取参考范围
    COUNT_EXPORT bool getLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits);
};


#endif // _REF_RANGE_H_