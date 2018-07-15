#ifndef _PROJECT_H_
#define _PROJECT_H_


#include <QString>

#include "libcommon.h"


// 项目
namespace Project
{
    // 自动加载
    COMMON_EXPORT bool load();

    // 项目信息
    COMMON_EXPORT bool isOem();

    COMMON_EXPORT QString project();
    COMMON_EXPORT void setProject(const QString& project);

    // 模式信息
    COMMON_EXPORT bool isDiff3Mode();
};


#endif // _PROJECT_H_