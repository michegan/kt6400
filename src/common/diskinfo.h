#ifndef _DISK_INFO_H_
#define _DISK_INFO_H_


#include <QStringList>

#include "libcommon.h"


// 磁盘信息
namespace DiskInfo
{
    // 获取U盘路径
    COMMON_EXPORT QStringList udisks();

    // 获取磁盘信息（单位：KB，返回总容量，剩余空间）
    COMMON_EXPORT double fdiskInfo(const QString& fdisk, double* volume = 0);
    COMMON_EXPORT double udiskInfo(const QString& udisk, double* volume = 0);
};


#endif // _DISK_INFO_H_