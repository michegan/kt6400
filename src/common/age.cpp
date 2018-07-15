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

// �ı���ʽֵ
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

// ��ʽ��
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

// ���䵥λ
QStringList Age::ageUnits()
{
    QStringList ageUnits;
    ageUnits << "Y" << "M" << "D";
    return ageUnits;
}

// ���ݳ������ڼ�������
Age Age::fromBirthdate(const QDate& date)
{
    QDate current = QDate::currentDate();

    // �������ڲ��ܳ�����ǰ����
    if (current <= date)
    {
        return Age();
    }

    // �������䣨��Ϊ3���Σ�0D-4W-2Y������2Y��λ�꣬С��28D��λ�죬������λ�£�
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

// ���䵥λ��ʽ��
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