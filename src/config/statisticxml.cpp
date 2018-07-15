#include "path.h"
#include "statisticxml.h"


StatisticXml::StatisticXml()
    : Xml(Path::configFilePath() + "statistic.xml")
{

}

StatisticXml::StatisticXml(const QString& fileName)
    : Xml(fileName)
{

}

StatisticXml::~StatisticXml()
{

}