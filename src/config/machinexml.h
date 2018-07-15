#ifndef _MACHINE_XML_H_
#define _MACHINE_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_MACHINE                ("MACHINE")

// KEY2�ؼ���
#define KEY2_SN                     ("SN")
#define KEY2_FOR_PETS               ("FOR_PETS")
#define KEY2_LANGUAGE               ("LANGUAGE")
#define KEY2_SYS_UNIT               ("SYS_UNIT")
#define KEY2_TEST_SPEED             ("TEST_SPEED")
#define KEY2_LYSE_VOLUME            ("LYSE_VOLUME")
#define KEY2_INSTALL_DATE           ("INSTALL_DATE")
#define KEY2_DILUENT_FACTOR         ("DILUENT_FACTOR")


// ������������ļ�����
class CONFIG_EXPORT MachineXml : public Xml
{
public:
    MachineXml();
    MachineXml(const QString& fileName);
    virtual ~MachineXml();
};


#endif // _MACHINE_XML_H_