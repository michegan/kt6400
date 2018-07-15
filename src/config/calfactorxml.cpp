#include <QtDebug>

#include "path.h"
#include "xmlnode.h"
#include "calfactorxml.h"


CalFactorXml::CalFactorXml()
    : Xml(Path::configFilePath() + "calfactor.xml")
{

}

CalFactorXml::CalFactorXml(const QString& fileName)
    : Xml(fileName)
{

}

CalFactorXml::~CalFactorXml()    
{

}

// У׼ϵ��
QList<CalFactor> CalFactorXml::getCalFactors(const QString& key1, const QString& key2)
{
    QList<CalFactor> factors;

    // ȡ��У׼ϵ���ڵ�
    XmlNode* xmlNode2 = this->getNode2(key1, key2);
    if (xmlNode2)
    {
        // ȡ��У׼ϵ���ڵ�
        QList<XmlNode*> xmlNodes3 = xmlNode2->childs();
        foreach (XmlNode* xmlNode3, xmlNodes3)
        {
            CalFactor factor;

            factor.id = xmlNode3->attribute("id");
            factor.value = xmlNode3->floatAttribute("value");
            factor.date = xmlNode3->attribute("date");

            factors.append(factor);
        }
    }
    else
    {
        qWarning() << "CalFactorXml getCalFactors getNode2 fail" << key1 << key2;
    }

    return factors;
}

bool CalFactorXml::setCalFactors(const QString& key1, const QString& key2, const QList<CalFactor>& factors)
{
    // ȡ��У׼ϵ���ڵ�
    XmlNode* xmlNode2 = this->getNode2(key1, key2);
    if (0 == xmlNode2)
    {
        qWarning() << "CalFactorXml setCalFactors getNode2 fail" << key1 << key2;
        return false;
    }

    // ȡ��У׼ϵ���ڵ�    
    QList<XmlNode*> xmlNodes3 = xmlNode2->childs();
    foreach (XmlNode* xmlNode3, xmlNodes3)
    {
        foreach (CalFactor factor, factors)
        {
            if (factor.id == xmlNode3->attribute("id"))
            {
                xmlNode3->setAttribute("value", factor.value);
                xmlNode3->setAttribute("date", factor.date);

                break;
            }
        }
    }

    return true;
}