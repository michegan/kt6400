#ifndef _LANGUAGE_XML_H_
#define _LANGUAGE_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_LANGUAGE               ("LANGUAGE")

// KEY2关键字
#define KEY2_CUR_UNIT               ("CUR_UNIT")
#define KEY2_DATE_FORMAT            ("DATE_FORMAT")


// 语言相关配置文件操作
class CONFIG_EXPORT LanguageXml : public Xml
{
public:
    LanguageXml();
    LanguageXml(const QString& fileName);
    virtual ~LanguageXml();
};


#endif // _LANGUAGE_XML_H_