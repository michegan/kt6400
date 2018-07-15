#ifndef _RESOURCE_H_
#define _RESOURCE_H_


#include <QImage>

#include "libcommon.h"


// 键盘资源
namespace Resource
{
    // 初始化
    COMMON_EXPORT void init();

    // 获取资源
    COMMON_EXPORT QImage* image(const QString& key);
};


#endif // _RESOURCE_H_