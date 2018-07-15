#ifndef _PATH_H_
#define _PATH_H_


#include <QString>

#include "libcommon.h"


// 通用路径
namespace Path
{
    // 根目录
    COMMON_EXPORT QString rootPath();
    COMMON_EXPORT void setRootPath(const QString& path);

    // 算法文件路径
    COMMON_EXPORT QString algFilePath();

    // 数据文件路径
    COMMON_EXPORT QString datFilePath();

    // 故障文件路径
    COMMON_EXPORT QString faultFilePath();

    // 配置文件路径
    COMMON_EXPORT QString configFilePath();

    // 系统默认文件路径
    COMMON_EXPORT QString defaultFilePath();
    COMMON_EXPORT QString defaultDatFilePath();
    COMMON_EXPORT QString defaultConfigFilePath();

    // 出厂默认文件路径
    COMMON_EXPORT QString factoryFilePath();
    COMMON_EXPORT QString factoryDatFilePath();
    COMMON_EXPORT QString factoryConfigFilePath();

    // 时序文件路径
    COMMON_EXPORT QString timeseqFilePath();
}


#endif // _PATH_H_