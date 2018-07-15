#ifndef _AGE_H_
#define _AGE_H_


#include <QDate>
#include <QStringList>

#include "libcommon.h"


// 年龄
class COMMON_EXPORT Age
{
public:
    // 年龄单位
    enum AgeUnit
    {
        AgeUnitYear = 0x01,
        AgeUnitMonth = 0x02,
        AgeUnitDay = 0x03,
    };

public:
    Age();
    Age(int ageVal, int ageUnit);
    virtual ~Age();

    // 文本格式值
    QString strAgeVal() const;
    QString strAgeUnit() const;

    // 格式化
    QString toString() const;
    void fromString(const QString& ageString);

public:
    // 年龄单位
    static QStringList ageUnits();

    // 根据出生日期计算年龄
    static Age fromBirthdate(const QDate& date);

    // 年龄单位格式化
    static Age::AgeUnit stringToAgeUnit(const QString& ageUnit);

public:
    // 年龄值
    int ageVal;

    // 年龄单位
    int ageUnit;
};


#endif // _AGE_H_