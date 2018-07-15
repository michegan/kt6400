#ifndef _UTILITY_H_
#define _UTILITY_H_


#include <QString>

#include "libcommon.h"


// 工具集
namespace Utility
{
    // 随机数
    COMMON_EXPORT int rand();

    // 随机数播种
    COMMON_EXPORT void srand();
    COMMON_EXPORT void srand(uint seed);

    // 生成GUID
    COMMON_EXPORT QString newGuid();

    // 浮点数格式化
    COMMON_EXPORT float format(float value, int dots);

    // 睡眠指定时间，屏蔽平台差异
    COMMON_EXPORT void ssleep(int secs);
    COMMON_EXPORT void msleep(int msecs);

    // 取指定字节（byte：字节索引值，取值范围[1，2，3，4]）
    COMMON_EXPORT quint8 lowerByte(qint16 value);
    COMMON_EXPORT quint8 lowerUByte(quint16 value);

    COMMON_EXPORT quint8 upperByte(qint16 value);
    COMMON_EXPORT quint8 upperUByte(quint16 value);

    COMMON_EXPORT quint8 getByte(int byte, qint32 value);
    COMMON_EXPORT quint8 getUByte(int byte, quint32 value);

    // 构造数值
    COMMON_EXPORT quint16 toUShort(quint8 byte0, quint8 byte1);
    COMMON_EXPORT quint32 toUInt(quint8 byte0, quint8 byte1, quint8 byte2, quint8 byte3);

    // 计算校验和（所有数据按照int类型相加，如果溢出则让其溢出，如果长度非4的整数倍，则放弃后续多余字节）
    COMMON_EXPORT int checkSum(const char* dataBuffer, int dataLen);

    // 读取文件数据（整个文件）
    COMMON_EXPORT char* getFileData(const QString& filename, int* fileLen = 0);

    // 创建目录
    COMMON_EXPORT bool mkPath(const QString& path);
    // 删除目录（含目录自身）
    COMMON_EXPORT bool rmPath(const QString& path);
    // 清空目录（不删除目录自身）
    COMMON_EXPORT bool clearPath(const QString& path);
    // 拷贝目录
    COMMON_EXPORT bool cpPath(const QString& srcPath, const QString& destPath);

    // 文件拷贝
    COMMON_EXPORT bool fileCopy(const QString& srcFileName, const QString& destFileName);
    COMMON_EXPORT bool fileCopy(const QString& fileName, const QString& srcFilePath, const QString& destFilePath);

    // 运行脚本（通用）
    COMMON_EXPORT bool runScript(const QString& script, bool print = true);
    // 运行脚本（相对/dymind/app/DM_****/script下的脚本）
    COMMON_EXPORT bool runAppScript(const QString& script);

    // 抓包
    COMMON_EXPORT void dump(const QByteArray& byteArray);
    COMMON_EXPORT void dump(const char* dataBuffer, int dataLen);


    // 版本比较（版本格式：0.1.0.9885 -> 0.2.0.1000）
    COMMON_EXPORT int compareNonAppVersion(const QString& version);
    // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
    COMMON_EXPORT int compareNonAppVersion(const QString& version1, const QString& version2);

    // 版本比较（版本格式：0.1.0.9885 -> 0.2.0.1000）
    COMMON_EXPORT int compareAppVersion(const QString& version);
    // 版本比较（版本格式：0.1.0.9885和0.2.0.1000）
    COMMON_EXPORT int compareAppVersion(const QString& version1, const QString& version2);


    // 压缩tar.bz2文件
    COMMON_EXPORT bool tarBz2File7z(const QString& fileName);
    COMMON_EXPORT bool tarBz2FileBzip2(const QString& fileName);
    // 压缩tar文件
    COMMON_EXPORT bool tarFile7z(const QString& path, const QString& fileName);

    // 解压缩tar.bz2文件
    COMMON_EXPORT bool extractTarBz2File7z(const QString& fileName);
    COMMON_EXPORT bool extractTarBz2FileBunzip2(const QString& fileName);
    // 解压缩tar文件
    COMMON_EXPORT bool extractTarFile7z(const QString& destPath, const QString& fileName);
}


#endif // _UTILITY_H_
