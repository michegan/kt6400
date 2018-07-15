#ifndef _PRINT_XML_H_
#define _PRINT_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_PRINT                   ("PRINT")

// KEY2�ؼ���
#define KEY2_PRINTER                 ("PRINTER")
#define KEY2_USB_REPORT              ("USB_REPORT")
#define KEY2_THERMAL_REPORT          ("THERMAL_REPORT")
#define KEY2_PRINT_GRAPH             ("PRINT_GRAPH")


// ��ӡ�����ļ�����
class CONFIG_EXPORT PrintXml : public Xml
{
public:
    PrintXml();
    PrintXml(const QString& fileName);
    virtual ~PrintXml();
};


#endif // _PRINT_XML_H_