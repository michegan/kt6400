#include "path.h"
#include "versionxml.h"


VersionXml::VersionXml()
    : Xml(Path::configFilePath() + "version.xml")
{

}

VersionXml::~VersionXml()    
{

}

VersionXml::VersionXml(const QString& fileName)
    : Xml(fileName)
{

}