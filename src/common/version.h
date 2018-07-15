#ifndef _VERSION_H_
#define _VERSION_H_


#include <QStringList>

#include "libcommon.h"


// �汾��
namespace Version
{
    // �ؼ���
    COMMON_EXPORT QStringList keys();

    // ��д�汾
    COMMON_EXPORT QString getVersion(const QString& key);
    COMMON_EXPORT void setVersion(const QString& key, const QString& version);

    // ���Ͱ汾
    COMMON_EXPORT QString getMtVersion();
    COMMON_EXPORT void setMtVersion(const QString& version);

    // ����ϵͳ�汾
    COMMON_EXPORT QString getOsVersion();
    COMMON_EXPORT void setOsVersion(const QString& version);

    // �㷨�汾
    COMMON_EXPORT QString getAlgVersion();
    COMMON_EXPORT void setAlgVersion(const QString& version);

    // ��������汾
    COMMON_EXPORT QString getMloVersion();
	COMMON_EXPORT void setMloVersion(const QString& version);

	COMMON_EXPORT QString getUbootVersion();
	COMMON_EXPORT void setUbootVersion(const QString& version);

    // ������MCU�汾
    COMMON_EXPORT QString getMcuVersion();
    COMMON_EXPORT void setMcuVersion(const QString& version);

    // ���ذ�FPGA�汾
    COMMON_EXPORT QString getFpgaVersion();
    COMMON_EXPORT void setFpgaVersion(const QString& version);

    // Ӧ�ó���汾
    COMMON_EXPORT QString getAppVersion();
    COMMON_EXPORT void setAppVersion(const QString& version);

};


#endif // _VERSION_H_