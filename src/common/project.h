#ifndef _PROJECT_H_
#define _PROJECT_H_


#include <QString>

#include "libcommon.h"


// ��Ŀ
namespace Project
{
    // �Զ�����
    COMMON_EXPORT bool load();

    // ��Ŀ��Ϣ
    COMMON_EXPORT bool isOem();

    COMMON_EXPORT QString project();
    COMMON_EXPORT void setProject(const QString& project);

    // ģʽ��Ϣ
    COMMON_EXPORT bool isDiff3Mode();
};


#endif // _PROJECT_H_