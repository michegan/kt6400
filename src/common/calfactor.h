#ifndef _CAL_FACTOR_H_
#define _CAL_FACTOR_H_


#include <QString>

#include "libcommon.h"


// 校准系数
class COMMON_EXPORT CalFactor
{
public:
    CalFactor();
    virtual ~CalFactor();

public:
    // 名称
    QString id;

    // 值
    float value;

    // 更改日期
    QString date;
};


#endif // _CAL_FACTOR_H_