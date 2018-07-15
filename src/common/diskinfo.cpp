#include <QtDebug>
#include <QSettings>

#include "utility.h"
#include "diskinfo.h"


// ������Ϣ
namespace DiskInfo
{
    // ��ȡ������Ϣ
    double diskInfo(const QString& filename, const QString& disk, double* volume)
    {
        QSettings settings(filename, QSettings::IniFormat);

        // �������ļ��ж�ȡ������Ϣ��28%��1013.5M��
        QString sused = settings.value(QString("%1/used").arg(disk), "0%").toString();
        QString svolume = settings.value(QString("%1/size").arg(disk), "0M").toString();

        // ������λ
        double unit = 1024;
        if (svolume.endsWith("M"))
        {
            unit *= 1024;
        }
        else if (svolume.endsWith("G"))
        {
            unit *= (1024 * 1024);
        }

        // ��Ϣ�ضϣ�28% -> 28��
        sused.chop(1);
        // ��Ϣ�ضϣ�1013.5M -> 1013.5��
        svolume.chop(1);

        // ��������
        double fvolume = unit * svolume.toDouble();
        double fused = fvolume * sused.toDouble() / 100.0;
 
        // ���ݷ���
        if (volume)
        {
            *volume = fvolume;
        }

        return (fvolume - fused);
    }

    // ��ȡU��·��
    QStringList udisks()
    {
        QStringList udisks;

        if (Utility::runAppScript("script/getudiskinfo.sh"))
        {
            QSettings settings("/dymind/app/ini/udiskinfo.ini", QSettings::IniFormat);
            udisks = settings.childGroups();
        }
        else
        {
            qDebug() << "DiskInfo udisks runAppScript fail";
        }

        return udisks;
    }

    // ��ȡ������Ϣ����λ��KB��������������ʣ��ռ䣩
    double fdiskInfo(const QString& fdisk, double* volume)
    {
        double space = 0;

        if (Utility::runAppScript("script/getfdiskinfo.sh"))
        {
            space = DiskInfo::diskInfo("/dymind/app/ini/fdiskinfo.ini", fdisk, volume);
        }
        else
        {
            qDebug() << "DiskInfo fdiskInfo runAppScript fail";
        }

        return space;
    }

    double udiskInfo(const QString& udisk, double* volume)
    {
        double space = 0;

        if (Utility::runAppScript("script/getudiskinfo.sh"))
        {
            space = DiskInfo::diskInfo("/dymind/app/ini/udiskinfo.ini", udisk, volume);
        }
        else
        {
            qDebug() << "DiskInfo udiskInfo runAppScript fail";
        }

        return space;
    }
}