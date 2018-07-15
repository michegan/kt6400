#include "age.h"


Age::Age()
    : ageVal(-1), ageUnit(Age::AgeUnitYear)
{

}

Age::Age(int val, int unit)
    : ageVal(val), ageUnit(unit)
{

}

Age::~Age()
{

}

// 文本格式值
QString Age::strAgeVal() const
{
    return (0 < this->ageVal ? QString::number(this->ageVal) : "");
}

QString Age::strAgeUnit() const
{
    if (Age::AgeUnitDay == this->ageUnit)
    {
        return "D";
    }
    else if (Age::AgeUnitMonth == this->ageUnit)
    {
        return "M";
    }
    else
    {
        return "Y";
    }
}

// 格式化
QString Age::toString() const
{
    return this->strAgeVal() + this->strAgeUnit();
}

void Age::fromString(const QString& ageString)
{
    if (ageString.isEmpty())
    {
        this->ageVal = -1;
        this->ageUnit = Age::AgeUnitYear;
    }
    else
    {
        QString ageUnit = ageString.right(1);
        QString ageVal = ageString.left(ageString.length() - 1);

        this->ageVal = ageVal.toInt();
        this->ageUnit = Age::stringToAgeUnit(ageUnit);
    }
}

// 年龄单位
QStringList Age::ageUnits()
{
    QStringList ageUnits;
    ageUnits << "Y" << "M" << "D";
    return ageUnits;
}

// 根据出生日期计算年龄
Age Age::fromBirthdate(const QDate& date)
{
    QDate current = QDate::currentDate();

    // 出生日期不能超过当前日期
    if (current <= date)
    {
        return Age();
    }

    // 计算年龄（分为3个段：0D-4W-2Y，超过2Y单位年，小于28D单位天，其他单位月）
    int years = current.year() - date.year();
    int months = (years * 12 + current.month() - date.month());
    int days = date.daysTo(current);

    if (2 < years)
    {
        return Age(years, Age::AgeUnitYear);
    }
    else if (days < 28)
    {
        return Age(days, Age::AgeUnitDay);
    }
    else
    {
        return Age(months, Age::AgeUnitMonth);
    }
}

// 年龄单位格式化
Age::AgeUnit Age::stringToAgeUnit(const QString& ageUnit)
{
    if ("D" == ageUnit)
    {
        return Age::AgeUnitDay;
    }
    else if ("M" == ageUnit)
    {
        return Age::AgeUnitMonth;
    }
    else
    {
        return Age::AgeUnitYear;
    }
}