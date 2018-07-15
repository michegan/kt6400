#ifndef _SAMPLE_ID_H_
#define _SAMPLE_ID_H_


#include <QString>

#include "libcommon.h"


// 样本编号
namespace SampleId
{
    // 本底样本编号
    COMMON_EXPORT QString background();

    // 样本编号是否有效
    COMMON_EXPORT bool isValid(const QString& sampleId);

    // 样本编号自动递增
    COMMON_EXPORT QString autoInc(const QString& sampleId);
};


#endif // _SAMPLE_ID_H_