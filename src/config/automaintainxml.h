#ifndef _AUTO_MAINTAIN_XML_H_
#define _AUTO_MAINTAIN_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_AUTO_MAINTAIN          ("AUTO_MAINTAIN")

// KEY2�ؼ���
#define KEY2_AUTO_CLEAN             ("AUTO_CLEAN")
#define KEY2_AUTO_SLEEP             ("AUTO_SLEEP")
#define KEY2_AUTO_PROBE_CLEAN       ("AUTO_PROBE_CLEAN")


// �Զ����������ļ�����
class CONFIG_EXPORT AutoMaintainXml : public Xml
{
public:
    AutoMaintainXml();
    AutoMaintainXml(const QString& fileName);
    virtual ~AutoMaintainXml();
};


#endif // _AUTO_MAINTAIN_XML_H_