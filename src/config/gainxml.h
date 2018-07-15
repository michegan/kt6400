#ifndef _GAIN_XML_H_
#define _GAIN_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_GAIN                   ("GAIN")

// KEY2�ؼ���
#define KEY2_WBC                    ("WBC")
#define KEY2_RBC                    ("RBC")
#define KEY2_HGB                    ("HGB")


// ���������ļ�����
class CONFIG_EXPORT GainXml : public Xml
{
public:
    GainXml();
    GainXml(const QString& fileName);
    virtual ~GainXml();
};


#endif // _GAIN_XML_H_