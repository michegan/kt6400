#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_


#include <QString>

#include "libcommon.h"


// ����
class COMMON_EXPORT Department
{
public:
    Department();
    virtual ~Department();

public:
    // ���Ҵ���
    QString deptId;

    // ������
    QString deptName;
};


#endif // _DEPARTMENT_H_