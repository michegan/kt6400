#include "path.h"
#include "machinexml.h"


MachineXml::MachineXml()
    : Xml(Path::configFilePath() + "machine.xml")
{

}

MachineXml::MachineXml(const QString& fileName)
    : Xml(fileName)
{

}

MachineXml::~MachineXml()
{

}