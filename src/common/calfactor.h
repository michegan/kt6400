#ifndef _CAL_FACTOR_H_
#define _CAL_FACTOR_H_


#include <QString>

#include "libcommon.h"


// У׼ϵ��
class COMMON_EXPORT CalFactor
{
public:
    CalFactor();
    virtual ~CalFactor();

public:
    // ����
    QString id;

    // ֵ
    float value;

    // ��������
    QString date;
};


#endif // _CAL_FACTOR_H_