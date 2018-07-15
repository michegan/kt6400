#ifndef _STATISTIC_XML_H_
#define _STATISTIC_XML_H_


#include "xml.h"
#include "libconfig.h"


// KEY1�ؼ���
#define KEY1_RUN_TIMES              ("RUN_TIMES")
#define KEY1_MAINTAIN_COUNT_TIMES   ("MAINTAIN_COUNT_TIMES")

// KEY2�ؼ���
#define KEY2_TOTAL_RUNTIME          ("TOTAL_RUNTIME")
#define KEY2_STARUP_RUNTIME         ("STARUP_RUNTIME")

#define KEY2_AUTO_CLEAN             ("AUTO_CLEAN")
#define KEY2_AUTO_PROBE_CLEAN       ("AUTO_PROBE_CLEAN")


// ͳ�������ļ�����
class CONFIG_EXPORT StatisticXml : public Xml
{
public:
    StatisticXml();
    StatisticXml(const QString& fileName);
    virtual ~StatisticXml();
};


#endif // _STATISTIC_XML_H_