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

    // 加载
    bool load();

    // 保存写入
    bool save();

    // 是否空
    bool isEmpty();

    // 由指定XML节点创建对应的协议节点
    XmlNode* fromDomElement(const QDomElement& rootElement);

public:
    // 文件名
    QString fileName;

    // 根节点
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

// 加载
bool XmlPrivate::load()
{
    QFile file(fileName);
    if (!file.open( QIODevice::ReadOnly))
    {
        qDebug() << "XmlPrivate load fail" << fileName;
        return false;
    }

    // 以文本流的形式访问
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close(); 

    // DOM结构解析
    QDomDocument domDocument;
    domDocument.setContent(content);
    QDomElement rootElement = domDocument.documentElement();

    rootNode = this->fromDomElement(rootElement);

    return (0 != rootNode);
}

// 保存写入
bool XmlPrivate::save()
{
    bool ret = false;

    do 
    {
        // 未加载，或加载错误
        if (0 == rootNode)
        {
            qDebug() << "XmlPrivate save fail ";
            break;
        }

        // 打开文件
        QFile file(fileName);
        if (!file.open( QIODevice::WriteOnly))
        {
            qDebug() << "XmlPrivate save open fail ";
            break;
        }

        // 以文本流的形式访问
        QTextStream stream(&file);
        stream << rootNode->toString();

        file.close();

        ret = true;
    } while (0);

    return ret;
}

// 是否空
bool XmlPrivate::isEmpty()
{
    bool ret = true;

    // 打开文件
    QFile file(fileName);
    if (file.open( QIODevice::ReadOnly))
    {
        // 长度为0就意味着文件空
        ret = (0 == file.size());

        // 关闭文件
        file.close();
    }
    else
    {
        qDebug() << "XmlPrivate isEmpty open fail";
    }

    return ret;
}

// 由指定XML节点创建对应的协议节点
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

// 加载
bool Xml::load()
{
    return d->load();
}

// 保存写入
bool Xml::save()
{
    return d->save();
}

// 文件检测
bool Xml::check()
{
    if (d->isEmpty())
    {
        // 文件空，则检测不通过
        return false;
    }
    else
    {
        // 文件加载成功，则认为检测通过
        return this->load();
    }
}

// 全部节点
QMap<QString, XmlNode*> Xml::allNodes()
{
    return this->allNodes("", d->rootNode);
}

QMap<QString, XmlNode*> Xml::allNodes(const QString& path, XmlNode* rootNode)
{
    QString newPath = path + rootNode->attribute(ATTR_ID);

    // 节点自身
    QMap<QString, XmlNode*> allNodes;
    allNodes.insert(newPath, rootNode);

    // 子节点
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

// 关键字（第一层子节点）
QStringList Xml::keys1()
{
    QStringList keys;

    // 根节点
    XmlNode* rootNode = d->rootNode;
    if (rootNode)
    {
        // 第一层子节点
        QList<XmlNode*> childNodes = rootNode->childs();
        foreach(XmlNode* child, childNodes)
        {
            QString key = child->attribute(ATTR_ID);
            keys.append(key);
        }
    }

    return keys;
}

// 关键字（第二层子节点）
QStringList Xml::keys2(const QString& key1)
{
    QStringList keys;

    // 第一层子节点
    XmlNode* rootNode = getNode1(key1);
    if (rootNode)
    {
        // 第二层子节点
        QList<XmlNode*> childNodes = rootNode->childs();
        foreach(XmlNode* childNode, childNodes)
        {
            QString id = childNode->attribute(ATTR_ID);
            keys.append(id);
        }
    }

    return keys;
}


// 获取值（第二层子节点）
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

    // 根节点
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

// 更新值（第二层子节点）
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

    // 根节点
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

// 根节点
XmlNode* Xml::rootNode()
{
    return d->rootNode;
}

// 取增益系数节点
XmlNode* Xml::getNode1(const QString& key1)
{
    QStringList keys;
    keys << key1;

    return this->getNode(keys);
}

// 在当前XML文件下，得到第一层子节点属性ID为key1的节点下，属性ID为key2的节点的指针
XmlNode* Xml::getNode2(const QString& key1, const QString& key2)
{
    QStringList keys;
    keys << key1 << key2;

    return this->getNode(keys);
}

// 在当前XML文件下，得到第一个ID为第一个key的节点的指针，继续循环直到最后一个ID为最后一个key的节点的指针
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

// 得到rootNode节点下属性ID为key的节点的指针
XmlNode* Xml::getNode(XmlNode* rootNode, const QString& key)
{
    XmlNode* xmlNode = 0;

    if (rootNode)
    {
        // 子节点
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

// XML文件升级
bool Xml::update(const QString& destFileName, const QString& srcFileName)
{
    bool ret = false;

    do 
    {
        // 加载源文件
        Xml xmlSrc(srcFileName);
        if (!xmlSrc.load())
        {
            qWarning() << "Xml update load fail" << srcFileName;
            break;
        }

        // 加载目标文件
        Xml xmlDest(destFileName);
        if (!xmlDest.load())
        {
            qWarning() << "Xml update load fail" << destFileName;
            break;
        }

        // 分别解析，得到对应节点列表
        QMap<QString, XmlNode*> srcNodes = xmlSrc.allNodes();
        QMap<QString, XmlNode*> destNodes = xmlDest.allNodes();

        // 文件升级
        if (!Xml::update(destNodes, srcNodes))
        {
            qWarning() << "Xml update update fail";
            break;
        }

        // 文件保存
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