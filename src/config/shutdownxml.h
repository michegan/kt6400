#ifndef _SHUTDOWN_XML_H_
#define _SHUTDOWN_XML_H_


#include <QDateTime>

#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_SHUTDOWN               ("SHUTDOWN")

// KEY2关键字
#define KEY2_SHUTDOWN_TYPE          ("SHUTDOWN_TYPE")
#define KEY2_SHUTDOWN_TIME          ("SHUTDOWN_TIME")

#define VALUE_SHUTDOWN_NORMAL       ("SHUTDOWN_NORMAL")
#define VALUE_SHUTDOWN_ABNORMAL     ("SHUTDOWN_ABNORMAL")
#define VALUE_SHUTDOWN_PACKAGE      ("SHUTDOWN_PACKAGE")


// 关机信息配置文件操作
class CONFIG_EXPORT ShutdownXml : public Xml
{
public:
    ShutdownXml();
    ShutdownXml(const QString& fileName);
    ~ShutdownXml();

    // 关机时间
    QDateTime getShutdownTime();
    bool setShutdownTime(const QDateTime& datetime);

private:
    // 日期时间格式
    QString datetimeFormat();
};


#endif // _SHUTDOWN_XML_H_