#include <QFile>
#include <QtDebug>
#include <QTextStream>
#include <QDomElement>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "xml.h"
#include "xmlnode.h"


class XmlPrivate
{
public:
    XmlPrivate();
    ~XmlPrivate();

    // ����
    bool load();

    // ����д��
    bool save();

    // �Ƿ��
    bool isEmpty();

    // ��ָ��XML�ڵ㴴����Ӧ��Э��ڵ�
    XmlNode* fromDomElement(const QDomElement& rootElement);

public:
    // �ļ���
    QString fileName;

    // ���ڵ�
    XmlNode* rootNode;
};


XmlPrivate::XmlPrivate()
    : fileName(""), rootNode(0)
{

}

XmlPrivate::~XmlPrivate()
{
    delete rootNode;
}

// ����
bool XmlPrivate::load()
{
    QFile file(fileName);
    if (!file.open( QIODevice::ReadOnly))
    {
        qDebug() << "XmlPrivate load fail" << fileName;
        return false;
    }

    // ���ı�������ʽ����
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close(); 

    // DOM�ṹ����
    QDomDocument domDocument;
    domDocument.setContent(content);
    QDomElement rootElement = domDocument.documentElement();

    rootNode = this->fromDomElement(rootElement);

    return (0 != rootNode);
}

// ����д��
bool XmlPrivate::save()
{
    bool ret = false;

    do 
    {
        // δ���أ�����ش���
        if (0 == rootNode)
        {
            qDebug() << "XmlPrivate save fail ";
            break;
        }

        // ���ļ�
        QFile file(fileName);
        if (!file.open( QIODevice::WriteOnly))
        {
            qDebug() << "XmlPrivate save open fail ";
            break;
        }

        // ���ı�������ʽ����
        QTextStream stream(&file);
        stream << rootNode->toString();

        file.close();

        ret = true;
    } while (0);

    return ret;
}

// �Ƿ��
bool XmlPrivate::isEmpty()
{
    bool ret = true;

    // ���ļ�
    QFile file(fileName);
    if (file.open( QIODevice::ReadOnly))
    {
        // ����Ϊ0����ζ���ļ���
        ret = (0 == file.size());

        // �ر��ļ�
        file.close();
    }
    else
    {
        qDebug() << "XmlPrivate isEmpty open fail";
    }

    return ret;
}

// ��ָ��XML�ڵ㴴����Ӧ��Э��ڵ�
XmlNode* XmlPrivate::fromDomElement(const QDomElement& rootElement)
{
    XmlNode* rootNode = new XmlNode(rootElement.tagName());

    QDomNode domNode = rootElement.firstChild();
    while (!domNode.isNull())
    {
        if (domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            XmlNode* childNode = this->fromDomElement(domElement);
            rootNode->appendChild(childNode);
        }

        domNode = domNode.nextSibling();
    }

    QDomNamedNodeMap attributes = rootElement.attributes();
    for (int i = 0; i < attributes.size(); i++)
    {
        QDomNode attrNode = attributes.item(i);
        rootNode->appendAttribute(attrNode.nodeName(), attrNode.nodeValue());
    }

    return rootNode;
}


Xml::Xml(const QString& fileName)
    : d(new XmlPrivate())
{
    d->fileName = fileName;
}

Xml::~Xml()
{
    delete d;
}

// ����
bool Xml::load()
{
    return d->load();
}

// ����д��
bool Xml::save()
{
    return d->save();
}

// �ļ����
bool Xml::check()
{
    if (d->isEmpty())
    {
        // �ļ��գ����ⲻͨ��
        return false;
    }
    else
    {
        // �ļ����سɹ�������Ϊ���ͨ��
        return this->load();
    }
}

// ȫ���ڵ�
QMap<QString, XmlNode*> Xml::allNodes()
{
    return this->allNodes("", d->rootNode);
}

QMap<QString, XmlNode*> Xml::allNodes(const QString& path, XmlNode* rootNode)
{
    QString newPath = path + rootNode->attribute(ATTR_ID);

    // �ڵ�����
    QMap<QString, XmlNode*> allNodes;
    allNodes.insert(newPath, rootNode);

    // �ӽڵ�
    QList<XmlNode*> xmlNodes = rootNode->childs();
    foreach (XmlNode* xmlNode, xmlNodes)
    {
        QMap<QString, XmlNode*> subNodes = this->allNodes(newPath, xmlNode);

        QMap<QString, XmlNode*>::const_iterator iter;
        for (iter = subNodes.constBegin(); iter != subNodes.constEnd(); iter++)
        {
            allNodes.insert(iter.key(), iter.value());
        }
    }

    return allNodes;
}

// �ؼ��֣���һ���ӽڵ㣩
QStringList Xml::keys1()
{
    QStringList keys;

    // ���ڵ�
    XmlNode* rootNode = d->rootNode;
    if (rootNode)
    {
        // ��һ���ӽڵ�
        QList<XmlNode*> childNodes = rootNode->childs();
        foreach(XmlNode* child, childNodes)
        {
            QString key = child->attribute(ATTR_ID);
            keys.append(key);
        }
    }

    return keys;
}

// �ؼ��֣��ڶ����ӽڵ㣩
QStringList Xml::keys2(const QString& key1)
{
    QStringList keys;

    // ��һ���ӽڵ�
    XmlNode* rootNode = getNode1(key1);
    if (rootNode)
    {
        // �ڶ����ӽڵ�
        QList<XmlNode*> childNodes = rootNode->childs();
        foreach(XmlNode* childNode, childNodes)
        {
            QString id = childNode->attribute(ATTR_ID);
            keys.append(id);
        }
    }

    return keys;
}


// ��ȡֵ���ڶ����ӽڵ㣩
float Xml::getFloatValue2(const QString& key1, const QString& key2)
{
    QString text = this->getTextValue2(key1, key2);
    return text.toFloat();
}

QString Xml::getTextValue2(const QString& key1, const QString& key2)
{
    return this->getTextAttribute2(key1, key2, ATTR_VALUE);
}

float Xml::getFloatAttribute2(const QString& key1, const QString& key2, const QString& attribute)
{
    QString text = this->getTextAttribute2(key1, key2, attribute);
    return text.toFloat();
}

QString Xml::getTextAttribute2(const QString& key1, const QString& key2, const QString& attribute)
{
    QString value;

    // ���ڵ�
    XmlNode* xmlNode = this->getNode2(key1, key2);
    if (xmlNode)
    {
        value = xmlNode->attribute(attribute);
    }
    else
    {
        qWarning() << "Xml getTextValue2 no node" << key1 << key2;
    }

    return value;
}

// ����ֵ���ڶ����ӽڵ㣩
bool Xml::setFloatValue2(const QString& key1, const QString& key2, float value)
{
    QString text = QString::number(value);
    return this->setTextValue2(key1, key2, text);
}

bool Xml::setTextValue2(const QString& key1, const QString& key2, const QString& value)
{
    return this->setTextAttribute2(key1, key2, value, ATTR_VALUE);
}

bool Xml::setTextAttribute2(const QString& key1, const QString& key2, const QString& value, const QString& attribute)
{
    bool ret = false;

    // ���ڵ�
    XmlNode* xmlNode = this->getNode2(key1, key2);
    if (xmlNode)
    {
        ret = xmlNode->setAttribute(attribute, value);
    }
    else
    {
        qWarning() << "Xml setTextValue2 no node" << key1 << key2;
    }

    return ret;
}

// ���ڵ�
XmlNode* Xml::rootNode()
{
    return d->rootNode;
}

// ȡ����ϵ���ڵ�
XmlNode* Xml::getNode1(const QString& key1)
{
    QStringList keys;
    keys << key1;

    return this->getNode(keys);
}

// �ڵ�ǰXML�ļ��£��õ���һ���ӽڵ�����IDΪkey1�Ľڵ��£�����IDΪkey2�Ľڵ��ָ��
XmlNode* Xml::getNode2(const QString& key1, const QString& key2)
{
    QStringList keys;
    keys << key1 << key2;

    return this->getNode(keys);
}

// �ڵ�ǰXML�ļ��£��õ���һ��IDΪ��һ��key�Ľڵ��ָ�룬����ѭ��ֱ�����һ��IDΪ���һ��key�Ľڵ��ָ��
XmlNode* Xml::getNode(const QStringList& keys)
{
    XmlNode* xmlNode = d->rootNode;

    foreach (QString key, keys)
    {
        xmlNode = this->getNode(xmlNode, key);
        if (0 == xmlNode)
        {
            break;
        }
    }

    return xmlNode;
}

// �õ�rootNode�ڵ�������IDΪkey�Ľڵ��ָ��
XmlNode* Xml::getNode(XmlNode* rootNode, const QString& key)
{
    XmlNode* xmlNode = 0;

    if (rootNode)
    {
        // �ӽڵ�
        QList<XmlNode*> childNodes = rootNode->childs();
        foreach(XmlNode* child, childNodes)
        {
            if (key == child->attribute(ATTR_ID))
            {
                xmlNode = child;
                break;
            }
        }
    }

    return xmlNode;
}

// XML�ļ�����
bool Xml::update(const QString& destFileName, const QString& srcFileName)
{
    bool ret = false;

    do 
    {
        // ����Դ�ļ�
        Xml xmlSrc(srcFileName);
        if (!xmlSrc.load())
        {
            qWarning() << "Xml update load fail" << srcFileName;
            break;
        }

        // ����Ŀ���ļ�
        Xml xmlDest(destFileName);
        if (!xmlDest.load())
        {
            qWarning() << "Xml update load fail" << destFileName;
            break;
        }

        // �ֱ�������õ���Ӧ�ڵ��б�
        QMap<QString, XmlNode*> srcNodes = xmlSrc.allNodes();
        QMap<QString, XmlNode*> destNodes = xmlDest.allNodes();

        // �ļ�����
        if (!Xml::update(destNodes, srcNodes))
        {
            qWarning() << "Xml update update fail";
            break;
        }

        // �ļ�����
        if (!xmlDest.save())
        {
            qWarning() << "Xml update save fail";
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

bool Xml::update(QMap<QString, XmlNode*>& destNodes, const QMap<QString, XmlNode*>& srcNodes)
{
    bool ret = true;

    QStringList keys = destNodes.keys();
    foreach (QString key, keys)
    {
        if (srcNodes.contains(key))
        {
            XmlNode* srcNode = srcNodes.value(key);
            XmlNode* destNode = destNodes.value(key);

            if (!XmlNode::update(destNode, srcNode))
            {
                ret = false;
                qWarning() << "Xml update update fail";

                break;
            }
        }
    }

    return ret;
}