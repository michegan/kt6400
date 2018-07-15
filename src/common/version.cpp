#include <QHash>
#include <QtDebug>

#include "version.h"


// 版本号
namespace Version
{
    // 版本信息
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

    // 关键字
    QStringList keys()
    {
        return s_versions.keys();
    }

    // 机型版本
    QString getMtVersion()
    {
        return Version::getVersion("MT");
    }

    void setMtVersion(const QString& version)
    {
        Version::setVersion("MT", version);
    }

    // 操作系统版本
    QString getOsVersion()
    {
        return Version::getVersion("OS");
    }

    void setOsVersion(const QString& version)
    {
        Version::setVersion("OS", version);
    }

    // 算法版本
    QString getAlgVersion()
    {
        return Version::getVersion("ALG");
    }

    void setAlgVersion(const QString& version)
    {
        Version::setVersion("ALG", version);
    }

    // 引导软件版本
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

    // 驱动板MCU版本
    QString getMcuVersion()
    {
        return Version::getVersion("MCU");
    }

    void setMcuVersion(const QString& version)
    {
        Version::setVersion("MCU", version);
    }

    // 驱动板FPGA版本
    QString getFpgaVersion()
    {
        return Version::getVersion("FPGA");
    }

    void setFpgaVersion(const QString& version)
    {
        Version::setVersion("FPGA", version);
    }

    // 应用程序版本
    QString getAppVersion()
    {
        return Version::getVersion("AS");
    }

    void setAppVersion(const QString& version)
    {
        Version::setVersion("AS", version);
    }
};