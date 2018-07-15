#include "path.h"
#include "languagexml.h"


LanguageXml::LanguageXml()
    : Xml(Path::configFilePath() + "language.xml")
{

}

LanguageXml::LanguageXml(const QString& fileName)
    : Xml(fileName)
{

}

LanguageXml::~LanguageXml()
{

}