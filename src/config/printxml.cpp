#include "path.h"
#include "printxml.h"


PrintXml::PrintXml()
    : Xml(Path::configFilePath() + "print.xml")
{

}

PrintXml::~PrintXml()
{

}

PrintXml::PrintXml(const QString& fileName)
    : Xml(fileName)
{

}