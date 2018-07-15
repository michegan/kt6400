#ifndef _GAIN_XML_H_
#define _GAIN_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_GAIN                   ("GAIN")

// KEY2关键字
#define KEY2_WBC                    ("WBC")
#define KEY2_RBC                    ("RBC")
#define KEY2_HGB                    ("HGB")


// 增益配置文件操作
class CONFIG_EXPORT GainXml : public Xml
{
public:
    GainXml();
    GainXml(const QString& fileName);
    virtual ~GainXml();
};


#endif // _GAIN_XML_H_