#ifndef _DISK_INFO_H_
#define _DISK_INFO_H_


#include <QStringList>

#include "libcommon.h"


// ������Ϣ
namespace DiskInfo
{
    // ��ȡU��·��
    COMMON_EXPORT QStringList udisks();

    // ��ȡ������Ϣ����λ��KB��������������ʣ��ռ䣩
    COMMON_EXPORT double fdiskInfo(const QString& fdisk, double* volume = 0);
    COMMON_EXPORT double udiskInfo(const QString& udisk, double* volume = 0);
};


#endif // _DISK_INFO_H_