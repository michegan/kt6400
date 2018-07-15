#include <QHash>
#include <QtDebug>

#include "version.h"


// �汾��
namespace Version
{
    // �汾��Ϣ
    QHash<QString, QString> s_versions;

    QString getVersion(const QString& key)
    {
        return s_versions.value(key, "");
    }

    void setVersion(const QString& key, const QString& version)
    {
        qDebug() << "Version setVersion" << key << version;

        if (s_versions.contains(key))
        {
            s_versions[key] = version;
        }
        else
        {
            s_versions.insert(key, version);
        }
    }

    // �ؼ���
    QStringList keys()
    {
        return s_versions.keys();
    }

    // ���Ͱ汾
    QString getMtVersion()
    {
        return Version::getVersion("MT");
    }

    void setMtVersion(const QString& version)
    {
        Version::setVersion("MT", version);
    }

    // ����ϵͳ�汾
    QString getOsVersion()
    {
        return Version::getVersion("OS");
    }

    void setOsVersion(const QString& version)
    {
        Version::setVersion("OS", version);
    }

    // �㷨�汾
    QString getAlgVersion()
    {
        return Version::getVersion("ALG");
    }

    void setAlgVersion(const QString& version)
    {
        Version::setVersion("ALG", version);
    }

    // ��������汾
    QString getMloVersion()
    {
        return Version::getVersion("MLO");
    }

    void setMloVersion(const QString& version)
    {
        Version::setVersion("MLO", version);
    }

    QString getUbootVersion()
    {
        return Version::getVersion("LS");
    }

    void setUbootVersion(const QString& version)
    {
        Version::setVersion("LS", version);
    }

    // ������MCU�汾
    QString getMcuVersion()
    {
        return Version::getVersion("MCU");
    }

    void setMcuVersion(const QString& version)
    {
        Version::setVersion("MCU", version);
    }

    // ������FPGA�汾
    QString getFpgaVersion()
    {
        return Version::getVersion("FPGA");
    }

    void setFpgaVersion(const QString& version)
    {
        Version::setVersion("FPGA", version);
    }

    // Ӧ�ó���汾
    QString getAppVersion()
    {
        return Version::getVersion("AS");
    }

    void setAppVersion(const QString& version)
    {
        Version::setVersion("AS", version);
    }
};