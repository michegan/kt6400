#ifndef _REF_RANGE_XML_H_
#define _REF_RANGE_XML_H_


#include "xml.h"
#include "para.h"
#include "libconfig.h"


// 属性
#define ATTR_LOW                    ("low")
#define ATTR_HIGH                   ("high")

// KEY1关键字
#define KEY1_ADULT_MALE             ("ADULT_MALE")
#define KEY1_ADULT_FEMALE           ("ADULT_FEMALE")
#define KEY1_CHILD                  ("CHILD")
#define KEY1_INFANT                 ("INFANT")

#define KEY1_DOG                    ("DOG")
#define KEY1_CAT                    ("CAT")
#define KEY1_MUOSE                  ("MUOSE")
#define KEY1_RABBIT                 ("RABBIT")

#define KEY1_USER_1                 ("USER_1")
#define KEY1_USER_2                 ("USER_1")
#define KEY1_USER_3                 ("USER_3")
#define KEY1_COMMON                 ("COMMON")


// 参考范围配置文件操作
class CONFIG_EXPORT RefRangeXml : public Xml
{
public:
    RefRangeXml();
    RefRangeXml(const QString& fileName);
    virtual ~RefRangeXml();

    // 参考范围
    bool refRange(const QString& key1, const QString& key2, ParaList& lowLimits, ParaList& highimits);
    bool setRefRange(const QString& key1, const QString& key2, const ParaList& lowLimits, const ParaList& highimits);
};


#endif // _REF_RANGE_XML_H_