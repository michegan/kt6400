#ifndef _VERSION_H_
#define _VERSION_H_


#include <QStringList>

#include "libcommon.h"


// 版本号
namespace Version
{
    // 关键字
    COMMON_EXPORT QStringList keys();

    // 读写版本
    COMMON_EXPORT QString getVersion(const QString& key);
    COMMON_EXPORT void setVersion(const QString& key, const QString& version);

    // 机型版本
    COMMON_EXPORT QString getMtVersion();
    COMMON_EXPORT void setMtVersion(const QString& version);

    // 操作系统版本
    COMMON_EXPORT QString getOsVersion();
    COMMON_EXPORT void setOsVersion(const QString& version);

    // 算法版本
    COMMON_EXPORT QString getAlgVersion();
    COMMON_EXPORT void setAlgVersion(const QString& version);

    // 引导软件版本
    COMMON_EXPORT QString getMloVersion();
	COMMON_EXPORT void setMloVersion(const QString& version);

	COMMON_EXPORT QString getUbootVersion();
	COMMON_EXPORT void setUbootVersion(const QString& version);

    // 驱动板MCU版本
    COMMON_EXPORT QString getMcuVersion();
    COMMON_EXPORT void setMcuVersion(const QString& version);

    // 主控板FPGA版本
    COMMON_EXPORT QString getFpgaVersion();
    COMMON_EXPORT void setFpgaVersion(const QString& version);

    // 应用程序版本
    COMMON_EXPORT QString getAppVersion();
    COMMON_EXPORT void setAppVersion(const QString& version);

};


#endif // _VERSION_H_