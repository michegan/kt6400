#ifndef _MACHINE_XML_H_
#define _MACHINE_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_MACHINE                ("MACHINE")

// KEY2关键字
#define KEY2_SN                     ("SN")
#define KEY2_FOR_PETS               ("FOR_PETS")
#define KEY2_LANGUAGE               ("LANGUAGE")
#define KEY2_SYS_UNIT               ("SYS_UNIT")
#define KEY2_TEST_SPEED             ("TEST_SPEED")
#define KEY2_LYSE_VOLUME            ("LYSE_VOLUME")
#define KEY2_INSTALL_DATE           ("INSTALL_DATE")
#define KEY2_DILUENT_FACTOR         ("DILUENT_FACTOR")


// 仪器相关配置文件操作
class CONFIG_EXPORT MachineXml : public Xml
{
public:
    MachineXml();
    MachineXml(const QString& fileName);
    virtual ~MachineXml();
};


#endif // _MACHINE_XML_H_