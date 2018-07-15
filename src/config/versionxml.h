#ifndef _VERSION_XML_H_
#define _VERSION_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_VERSION                ("VERSION")

// KEY2关键字
#define KEY2_UBOOT                  ("UBOOT")
#define KEY2_KERNEL                 ("KERNEL")

#define KEY2_APP                    ("APP")
#define KEY2_ALG                    ("ALG")
#define KEY2_TIMESEQ                ("TIMESEQ")

#define KEY2_MCU                    ("MCU")
#define KEY2_FPGA                   ("FPGA")


// 版本信息配置文件操作
class CONFIG_EXPORT VersionXml : public Xml
{
public:
    VersionXml();
    VersionXml(const QString& fileName);
    virtual ~VersionXml();
};


#endif // _VERSION_XML_H_