#ifndef _RESOURCE_H_
#define _RESOURCE_H_


#include <QImage>

#include "libcommon.h"


// ������Դ
namespace Resource
{
    // ��ʼ��
    COMMON_EXPORT void init();

    // ��ȡ��Դ
    COMMON_EXPORT QImage* image(const QString& key);
};


#endif // _RESOURCE_H_