#ifndef _PARA_UNITS_XML_H_
#define _PARA_UNITS_XML_H_


#include "xml.h"
#include "calfactor.h"
#include "libconfig.h"


// 参数单位配置文件操作
class CONFIG_EXPORT ParaUnitsXml : public Xml
{
public:
    ParaUnitsXml();
    ParaUnitsXml(const QString& fileName);
    virtual ~ParaUnitsXml();
};


#endif // _PARA_UNITS_XML_H_