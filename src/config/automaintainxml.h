#ifndef _AUTO_MAINTAIN_XML_H_
#define _AUTO_MAINTAIN_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_AUTO_MAINTAIN          ("AUTO_MAINTAIN")

// KEY2关键字
#define KEY2_AUTO_CLEAN             ("AUTO_CLEAN")
#define KEY2_AUTO_SLEEP             ("AUTO_SLEEP")
#define KEY2_AUTO_PROBE_CLEAN       ("AUTO_PROBE_CLEAN")


// 自动休眠配置文件操作
class CONFIG_EXPORT AutoMaintainXml : public Xml
{
public:
    AutoMaintainXml();
    AutoMaintainXml(const QString& fileName);
    virtual ~AutoMaintainXml();
};


#endif // _AUTO_MAINTAIN_XML_H_