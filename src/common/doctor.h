#ifndef _DOCTOR_H_
#define _DOCTOR_H_


#include <QString>

#include "libcommon.h"


// ҽ��
class COMMON_EXPORT Doctor
{
public:
    Doctor();
    virtual ~Doctor();

public:
    // ҽ����
    QString doctorId;

    // ҽ����
    QString doctorName;

    // ���Һ�
    QString deptId;
};


#endif // _DOCTOR_H_