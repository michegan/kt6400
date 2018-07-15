#include <QDir>
#include <QMap>
#include <QtDebug>
#include <QFileInfoList>

#include "path.h"
#include "resource.h"


// 键盘资源
namespace Resource
{
    // 图片资源
    QMap<QString, QImage*> s_images;

    // 初始化
    void init()
    {
        qDebug() << "Resource init";

        // 资源文件路径
        QString path = Path::rootPath() + "image/";
        QDir dir(path);

        // 加载该路径下的所有图片资源
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

    // 获取资源
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