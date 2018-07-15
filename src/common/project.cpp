#include <QSettings>

#include "path.h"
#include "project.h"


// ��Ŀ
namespace Project
{
    // ��Ŀ��Ϣ
    static QString s_project = "";

    // �Զ�����
    bool load()
    {
        // ��Ŀ����
        QString key = "CONFIG/Project";
        QString filename = Path::configFilePath() + "project.ini";

        QSettings settings(filename, QSettings::IniFormat, 0);
        if (settings.contains(key))
        {
            s_project = settings.value(key).toString();
        }

        return true;
    }

    // ��Ŀ��Ϣ
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

    // ģʽ��Ϣ
    bool isDiff3Mode()
    {
        return true;
    }
}
