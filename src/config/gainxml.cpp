#include "path.h"
#include "gainxml.h"


GainXml::GainXml()
    : Xml(Path::configFilePath() + "gain.xml")
{

}

GainXml::~GainXml()
{

}

GainXml::GainXml(const QString& fileName)
    : Xml(fileName)
{

}