#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_


#include <QString>

#include "libcommon.h"


// 科室
class COMMON_EXPORT Department
{
public:
    Department();
    virtual ~Department();

public:
    // 科室代码
    QString deptId;

    // 科室名
    QString deptName;
};


#endif // _DEPARTMENT_H_