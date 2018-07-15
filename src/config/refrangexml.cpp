#include <QtDebug>

#include "path.h"
#include "xmlnode.h"
#include "refrangexml.h"


RefRangeXml::RefRangeXml()
    : Xml(Path::configFilePath() + "refrange.xml")
{

}

RefRangeXml::RefRangeXml(const QString& fileName)
    : Xml(fileName)
{

}

RefRangeXml::~RefRangeXml()    
{

}

// ²Î¿¼·¶Î§
bool RefRangeXml::refRange(const QString& key1, const QString& key2, ParaList& lowLimits, ParaList& highimits)
{
    bool ret = false;

    XmlNode* xmlNode2 = this->getNode2(key1, key2);
    if (xmlNode2)
    {
        lowLimits.clear();
        highimits.clear();

        const QList<XmlNode*> xmlNodes3 = xmlNode2->childs();
        foreach (XmlNode* xmlNode3, xmlNodes3)
        {
            QString name = xmlNode3->attribute(ATTR_ID);
            float low = xmlNode3->floatAttribute(ATTR_LOW);
            float high = xmlNode3->floatAttribute(ATTR_HIGH);

            lowLimits.appendPara(name, low);
            highimits.appendPara(name, high);
        }

        ret = true;
    }
    else
    {
        qWarning() << "RefRangeXml refRange getNode2 fail" << key1 << key2;
    }

    return ret;
}

bool RefRangeXml::setRefRange(const QString& key1, const QString& key2, const ParaList& lowLimits, const ParaList& highimits)
{
    bool ret = false;

    XmlNode* xmlNode2 = this->getNode2(key1, key2);
    if (xmlNode2)
    {
        foreach (Para para, lowLimits)
        {
            XmlNode* xmlNode3 = xmlNode2->child(para.name);
            if (xmlNode3)
            {
                xmlNode3->setAttribute(ATTR_LOW, para.value);
            }
        }

        foreach (Para para, highimits)
        {
            XmlNode* xmlNode3 = xmlNode2->child(para.name);
            if (xmlNode3)
            {
                xmlNode3->setAttribute(ATTR_HIGH, para.value);
            }
        }

        ret = true;
    }
    else
    {
        qWarning() << "RefRangeXml setRefRange getNode2 fail" << key1 << key2;
    }    

    return ret;
}