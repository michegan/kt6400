#include <QSettings>

#include "path.h"
#include "project.h"


// 项目
namespace Project
{
    // 项目信息
    static QString s_project = "";

    // 自动加载
    bool load()
    {
        // 项目名称
        QString key = "CONFIG/Project";
        QString filename = Path::configFilePath() + "project.ini";

        QSettings settings(filename, QSettings::IniFormat, 0);
        if (settings.contains(key))
        {
            s_project = settings.value(key).toString();
        }

        return true;
    }

    // 项目信息
    bool isOem()
    {
        return (QString("XXXX").length() < s_project.length());
    }

    QString project()
    {
        return s_project;
    }

    void setProject(const QString& project)
    {
        s_project = project;
    }

    // 模式信息
    bool isDiff3Mode()
    {
        return true;
    }
}
