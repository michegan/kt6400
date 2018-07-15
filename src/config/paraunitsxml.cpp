#include <QtDebug>

#include "path.h"
#include "xmlnode.h"
#include "paraunit.h"
#include "paraunitsxml.h"


ParaUnitsXml::ParaUnitsXml()
    : Xml(Path::configFilePath() + "paraunits.xml")
{

}

ParaUnitsXml::ParaUnitsXml(const QString& fileName)
    : Xml(fileName)
{

}

ParaUnitsXml::~ParaUnitsXml()    
{

}