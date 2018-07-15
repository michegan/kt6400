#ifndef _PARA_UNIT_XML_H_
#define _PARA_UNIT_XML_H_


#include "xml.h"
#include "calfactor.h"
#include "libconfig.h"


// ����
#define ATTR_FORMAT                 ("format")

// KEY1�ؼ���
#define KEY1_CHINA                  ("CHINA")
#define KEY1_CURRENT                ("CURRENT")
#define KEY1_INTERNAL               ("INTERNAL")


// ������λ�����ļ�����
class CONFIG_EXPORT ParaUnitXml : public Xml
{
public:
    ParaUnitXml();
    ParaUnitXml(const QString& fileName);
    virtual ~ParaUnitXml();
};


#endif // _PARA_UNIT_XML_H_