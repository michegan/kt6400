#include "path.h"
#include "automaintainxml.h"


AutoMaintainXml::AutoMaintainXml()
    : Xml(Path::configFilePath() + "automaintain.xml")
{

}

AutoMaintainXml::AutoMaintainXml(const QString& fileName)
    : Xml(fileName)
{

}

AutoMaintainXml::~AutoMaintainXml()
{

}