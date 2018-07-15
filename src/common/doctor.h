#ifndef _DOCTOR_H_
#define _DOCTOR_H_


#include <QString>

#include "libcommon.h"


// 医生
class COMMON_EXPORT Doctor
{
public:
    Doctor();
    virtual ~Doctor();

public:
    // 医生号
    QString doctorId;

    // 医生名
    QString doctorName;

    // 科室号
    QString deptId;
};


#endif // _DOCTOR_H_