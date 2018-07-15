#ifndef _CACHE_H_
#define _CACHE_H_


#include <QStringList>

#include "user.h"
#include "para.h"
#include "modes.h"
#include "sysstate.h"
#include "calfactor.h"
#include "libcommon.h"


// 缓存
namespace Cache
{
    // 当前用户
    COMMON_EXPORT User* currentUser();

    // 当前系统状态
    COMMON_EXPORT SysState* sysState();

    // 仪器相关配置
    COMMON_EXPORT bool isForPets();
    COMMON_EXPORT void setForPets(bool forPets);

    // 校准系数
    COMMON_EXPORT float getCalFactor(const Modes& modes, const QString& para);

    COMMON_EXPORT QList<CalFactor> getCalFactors(const QString& key1, const QString& key2);
    COMMON_EXPORT void setCalFactors(const QString& key1, const QString& key2, const QList<CalFactor>& calFactors);

    // 参考范围缓存
    COMMON_EXPORT QStringList refRangeKeys1();
    COMMON_EXPORT QStringList refRangeKeys2(const QString& key1);

    COMMON_EXPORT bool refRange(const QString& key1, const QString& key2, ParaList& lowLimits, ParaList& highLimits);
    COMMON_EXPORT void setRefRange(const QString& key1, const QString& key2, const ParaList& lowLimits, const ParaList& highLimits);
};


#endif // _CACHE_H_