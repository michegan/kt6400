#ifndef _AGE_H_
#define _AGE_H_


#include <QDate>
#include <QStringList>

#include "libcommon.h"


// ����
class COMMON_EXPORT Age
{
public:
    // ���䵥λ
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

    // �ı���ʽֵ
    QString strAgeVal() const;
    QString strAgeUnit() const;

    // ��ʽ��
    QString toString() const;
    void fromString(const QString& ageString);

public:
    // ���䵥λ
    static QStringList ageUnits();

    // ���ݳ������ڼ�������
    static Age fromBirthdate(const QDate& date);

    // ���䵥λ��ʽ��
    static Age::AgeUnit stringToAgeUnit(const QString& ageUnit);

public:
    // ����ֵ
    int ageVal;

    // ���䵥λ
    int ageUnit;
};


#endif // _AGE_H_