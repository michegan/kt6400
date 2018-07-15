#include <QtDebug>

#include "path.h"
#include "xmlnode.h"
#include "paraunit.h"
#include "paraunitxml.h"


ParaUnitXml::ParaUnitXml()
    : Xml(Path::configFilePath() + "paraunit.xml")
{

}

ParaUnitXml::ParaUnitXml(const QString& fileName)
    : Xml(fileName)
{

}

ParaUnitXml::~ParaUnitXml()    
{

}