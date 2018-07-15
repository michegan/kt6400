#ifndef _CAL_FACTOR_XML_H_
#define _CAL_FACTOR_XML_H_


#include "xml.h"
#include "calfactor.h"
#include "libconfig.h"


// KEY1关键字
#define KEY1_USER                   ("IDS_USER")
#define KEY1_FACTORY                ("IDS_FACTORY")

#define KEY2_WHOLE_BLOOD            ("IDS_WHOLE_BLOOD")
#define KEY2_PERIPHERAL             ("IDS_PERIPHERAL")
#define KEY2_PREDILUENT             ("IDS_PREDILUENT")


// 校准系数配置文件操作
class CONFIG_EXPORT CalFactorXml : public Xml
{
public:
    CalFactorXml();
    CalFactorXml(const QString& fileName);
    ~CalFactorXml();

    // 校准系数
    QList<CalFactor> getCalFactors(const QString& key1, const QString& key2);
    bool setCalFactors(const QString& key1, const QString& key2, const QList<CalFactor>& factors);
};


#endif // _CAL_FACTOR_XML_H_