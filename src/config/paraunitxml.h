#ifndef _PARA_UNIT_XML_H_
#define _PARA_UNIT_XML_H_


#include "xml.h"
#include "calfactor.h"
#include "libconfig.h"


// 属性
#define ATTR_FORMAT                 ("format")

// KEY1关键字
#define KEY1_CHINA                  ("CHINA")
#define KEY1_CURRENT                ("CURRENT")
#define KEY1_INTERNAL               ("INTERNAL")


// 参数单位配置文件操作
class CONFIG_EXPORT ParaUnitXml : public Xml
{
public:
    ParaUnitXml();
    ParaUnitXml(const QString& fileName);
    virtual ~ParaUnitXml();
};


#endif // _PARA_UNIT_XML_H_