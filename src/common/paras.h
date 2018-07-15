#ifndef _PARAS_H_
#define _PARAS_H_


#include <QStringList>

#include "libcommon.h"


// 项目参数
namespace Paras
{
    // 所有质控参数
    COMMON_EXPORT QStringList qcParaNames();

    // 所有校准参数
    COMMON_EXPORT QStringList calibrateParaNames();

    // 分析模式对应的所有报告参数
    COMMON_EXPORT QStringList reportParaNames();

    COMMON_EXPORT QStringList wbcReportParaNames();
    COMMON_EXPORT QStringList rbcReportParaNames();
    COMMON_EXPORT QStringList pltReportParaNames();

    // 参数描述
    COMMON_EXPORT QString paraIds(const QString& paraName);
};


#endif // _PARAS_H_