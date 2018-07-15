#include <QMap>
#include <QFile>
#include <QtDebug>
#include <QTextStream>

#include "language.h"


// 语言
namespace Language
{
    // 字符串信息
    static QMap<QString, QString> s_strings;

    // 获取字符串
    QString getString(const QString& ids)
    {
        return s_strings.value(ids, ids);
    }

    // 语言加载
    bool load(const QString& fileName)
    {
        qDebug() << "Language load" << fileName;

        QFile file(fileName);

        bool ret = file.open(QIODevice::ReadOnly | QIODevice::Text);
        if (ret)
        {
            QTextStream stream(&file);
            while (!stream.atEnd())
            {
                // 例如：102 : WBC
                QString line = stream.readLine();

                int index = line.indexOf(":");
                if (0 < index)
                {
                    // 分别提取ID和值
                    QString ids = line.left(index).trimmed();
                    QString value = line.mid(index + 1).trimmed();

                    s_strings.insert(ids, value);
                }
                else
                {
                    qWarning() << "Language load invalid line" << line;
                }
            }

            file.close();
        }
        else
        {
            qWarning() << "Language load open fail";
        }

        return ret;
    }
}