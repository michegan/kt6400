#include "path.h"
#include "xmlnode.h"
#include "shutdownxml.h"


ShutdownXml::ShutdownXml()
    : Xml(Path::configFilePath() + "shutdown.xml")
{

}

ShutdownXml::ShutdownXml(const QString& fileName)
    : Xml(fileName)
{

}

ShutdownXml::~ShutdownXml()    
{

}

// 关机时间
QDateTime ShutdownXml::getShutdownTime()
{
    QString text = this->getTextValue2(KEY1_SHUTDOWN, KEY2_SHUTDOWN_TIME);
    if (text.isEmpty())
    {
        return QDateTime::currentDateTime();
    }
    else
    {
        QString format = this->datetimeFormat();
        return QDateTime::fromString(text, format);
    }
}

bool ShutdownXml::setShutdownTime(const QDateTime& datetime)
{
    QString format = this->datetimeFormat();
    QString text = datetime.toString(format);

    return this->setTextValue2(KEY1_SHUTDOWN, KEY2_SHUTDOWN_TIME, text);
}

// 日期时间格式
QString ShutdownXml::datetimeFormat()
{
    return "yyyy-MM-dd HH:mm";
}