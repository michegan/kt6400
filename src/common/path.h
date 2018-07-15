#ifndef _PATH_H_
#define _PATH_H_


#include <QString>

#include "libcommon.h"


// ͨ��·��
namespace Path
{
    // ��Ŀ¼
    COMMON_EXPORT QString rootPath();
    COMMON_EXPORT void setRootPath(const QString& path);

    // �㷨�ļ�·��
    COMMON_EXPORT QString algFilePath();

    // �����ļ�·��
    COMMON_EXPORT QString datFilePath();

    // �����ļ�·��
    COMMON_EXPORT QString faultFilePath();

    // �����ļ�·��
    COMMON_EXPORT QString configFilePath();

    // ϵͳĬ���ļ�·��
    COMMON_EXPORT QString defaultFilePath();
    COMMON_EXPORT QString defaultDatFilePath();
    COMMON_EXPORT QString defaultConfigFilePath();

    // ����Ĭ���ļ�·��
    COMMON_EXPORT QString factoryFilePath();
    COMMON_EXPORT QString factoryDatFilePath();
    COMMON_EXPORT QString factoryConfigFilePath();

    // ʱ���ļ�·��
    COMMON_EXPORT QString timeseqFilePath();
}


#endif // _PATH_H_