#ifndef _LANGUAGE_XML_H_
#define _LANGUAGE_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_LANGUAGE               ("LANGUAGE")

// KEY2�ؼ���
#define KEY2_CUR_UNIT               ("CUR_UNIT")
#define KEY2_DATE_FORMAT            ("DATE_FORMAT")


// ������������ļ�����
class CONFIG_EXPORT LanguageXml : public Xml
{
public:
    LanguageXml();
    LanguageXml(const QString& fileName);
    virtual ~LanguageXml();
};


#endif // _LANGUAGE_XML_H_