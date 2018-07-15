#include <QDir>
#include <QMap>
#include <QtDebug>
#include <QFileInfoList>

#include "path.h"
#include "resource.h"


// ������Դ
namespace Resource
{
    // ͼƬ��Դ
    QMap<QString, QImage*> s_images;

    // ��ʼ��
    void init()
    {
        qDebug() << "Resource init";

        // ��Դ�ļ�·��
        QString path = Path::rootPath() + "image/";
        QDir dir(path);

        // ���ظ�·���µ�����ͼƬ��Դ
        QStringList nameFilters;
        nameFilters.append("*.png");
        nameFilters.append("*.jpg");

        QFileInfoList fileInfos = dir.entryInfoList(nameFilters);
        foreach (QFileInfo fileInfo, fileInfos)
        {
            QImage* image = new QImage(fileInfo.filePath());
            if (image)
            {
                s_images.insert(fileInfo.fileName(), image);
            }
        }
    }

    // ��ȡ��Դ
    QImage* image(const QString& key)
    {
        QImage* image = s_images.value(key + ".png", 0);
        if (0 == image)
        {
            image = s_images.value(key + ".jpg", 0);
            if (0 == image)
            {
                qWarning() << "Resource image no image" << key;
            }
        }
        return image;
    }
};