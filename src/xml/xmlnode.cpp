#include <QPair>
#include <QDebug>
#include <QAtomicInt>
#include <QDomElement>
#include <QDomDocument>

#include "xml.h"
#include "xmlnode.h"


class XmlNodePrivate
{
public:
    XmlNodePrivate();
    ~XmlNodePrivate();

    // 字节流格式化
    QString byteArrayToString(const QByteArray& byteArray);

    // 向本节点添加属性
    bool appendAttribute(const QString& attrName, const QString& attrValue);

    // 创建Dom文档
    QDomElement createDomElement(QDomDocument& domDocument, const XmlNode* rootNode);

    // 添加DOM节点属性
    void addDomAttribute(QDomDocument& domDocument, QDomElement& domElement, const XmlNode* rootNode);

public:
    // 节点名称
    QString name;

    // 引用计数
    QAtomicInt* atomic;

    // 所有子节点
    QList<XmlNode*> childs;
    QList<QPair<QString, QString> > attributes;
};

XmlNodePrivate::XmlNodePrivate()
    : atomic(new QAtomicInt(1))
{

}

XmlNodePrivate::~XmlNodePrivate()
{
    delete atomic;
    foreach(XmlNode* child, childs)
    {
        delete child;
    }
}

// 字节流格式化
QString XmlNodePrivate::byteArrayToString(const QByteArray& byteArray)
{
    QString string;

    int size = byteArray.size();
    for (int i = 0; i < size; i++)
    {
        int v = byteArray.at(i);
        QString str = QString("%1").arg(v, 2, 16, QLatin1Char('0'));

        string += str;
    }

    return string;
}

// 向本节点添加属性
bool XmlNodePrivate::appendAttribute(const QString& attrName, const QString& attrValue)
{
    attributes.append(qMakePair(attrName, attrValue));
    return true;
}

// 创建Dom文档
QDomElement XmlNodePrivate::createDomElement(QDomDocument& domDocument, const XmlNode* rootNode)
{
    // 当前节点；
    QDomElement rootElement = domDocument.createElement(rootNode->d->name);

    // 当前节点的所有子节点；
    QDomElement domElement;
    for(int i = 0; i < rootNode->d->childs.size(); i++)
    {
        // 子节点又递归创建对应的Dom对象；
        const XmlNode* childNode = rootNode->d->childs.at(i);
        domElement = childNode->d->createDomElement(domDocument, childNode);
        rootElement.appendChild(domElement);
    }

    // 最后是当前节点的属性信息；
    rootNode->d->addDomAttribute(domDocument, rootElement, rootNode);

    return rootElement;
}

// 添加DOM节点属性
void XmlNodePrivate::addDomAttribute(QDomDocument& domDocument, QDomElement& domElement, const XmlNode* rootNode)
{
    // 向domElement添加属性
    QDomAttr domAttribute;
    for(int i = 0; i < rootNode->d->attributes.size(); i++)
    {
        const QPair<QString, QString>& pair = rootNode->d->attributes.at(i);

        // 创建属性并设置属性值
        domAttribute = domDocument.createAttribute(pair.first);
        domAttribute.setValue(pair.second);

        domElement.setAttributeNode(domAttribute);
    }
}


XmlNode::XmlNode()
    : d(new XmlNodePrivate())
{

}

XmlNode::XmlNode(const QString& name)
    : d(new XmlNodePrivate())
{
    d->name = name;
}

XmlNode::XmlNode(const XmlNode& other)
{
    this->d = other.d;
}

XmlNode::~XmlNode()
{
    if (!d->atomic->deref())
    {
        delete d;
    }
}

// 名称
QString XmlNode::name() const
{
    return d->name;
}

void XmlNode::setName(const QString& name)
{
    d->name = name;
}

// 添加子节点
XmlNode* XmlNode::appendChild(const QString& tagName)
{
    XmlNode* subNode = new XmlNode(tagName);
    return this->appendChild(subNode);
}

XmlNode* XmlNode::appendChild(XmlNode* child)
{
    if (child)
    {
        d->childs.append(child);
    }
    return child;
}

// 添加节点属性
bool XmlNode::appendAttribute(const QString& attrName, int attrValue)
{
    return d->appendAttribute(attrName, QString::number(attrValue));
}

bool XmlNode::appendAttribute(const QString& attrName, float attrValue)
{
    return d->appendAttribute(attrName, QString::number(attrValue));
}

bool XmlNode::appendAttribute(const QString& attrName, const QString& attrValue)
{
    return d->appendAttribute(attrName, attrValue);
}

// 获取子节点
QList<XmlNode*> XmlNode::childs() const
{
    return d->childs;
}


XmlNode* XmlNode::firstChild() const
{
    XmlNode* node = 0;

    if (!d->childs.isEmpty())
    {
        node = d->childs.first();
    }

    return node;
}

XmlNode* XmlNode::child(const QString& id) const
{
    foreach (XmlNode* node, d->childs)
    {
        QString sid = node->attribute(ATTR_ID);
        if (id == sid)
        {
            return node;
        }
    }
    return 0;
}

// 向本节点添加属性
bool XmlNode::setAttribute(const QString& attrName, int attrValue)
{
    QString strAttrValue = QString::number(attrValue);
    return this->setAttribute(attrName, strAttrValue);
}

bool XmlNode::setAttribute(const QString& attrName, bool attrValue)
{
    QString strAttrValue = (attrValue ? "YES" : "NO");
    return this->setAttribute(attrName, strAttrValue);
}

bool XmlNode::setAttribute(const QString& attrName, float attrValue)
{
    QString strAttrValue = QString::number(attrValue);
    return this->setAttribute(attrName, strAttrValue);
}

bool XmlNode::setAttribute(const QString& attrName, const QString& attrValue)
{
    for (int i = 0; i < d->attributes.size(); i++)
    {
        QPair<QString, QString>& pair = d->attributes[i];
        if (pair.first == attrName)
        {
            pair.second = attrValue;
            return true;
        }
    }
    return false;
}

// 获取节点属性
QStringList XmlNode::attributes() const
{
    QStringList keys;
    for (int i = 0; i < d->attributes.size(); i++)
    {
        QPair<QString, QString> pair = d->attributes.at(i);
        keys.append(pair.first);
    }
    return keys;
}

QString XmlNode::attribute(const QString& attrName) const
{
    QString attrValue;
    for (int i = 0; i < d->attributes.size(); i++)
    {
        QPair<QString, QString> pair = d->attributes.at(i);
        if (pair.first == attrName)
        {
            attrValue = pair.second;
            break;
        }
    }
    return attrValue;
}

int XmlNode::intAttribute(const QString& attrName) const
{
    QString attrValue = this->attribute(attrName);
    return attrValue.toInt();
}

bool XmlNode::boolAttribute(const QString& attrName) const
{
    QString attrValue = this->attribute(attrName);
    return ("YES" == attrValue);
}

float XmlNode::floatAttribute(const QString& attrName) const
{
    QString attrValue = this->attribute(attrName);
    return attrValue.toFloat();
}

// 编码
QString XmlNode::toString() const
{
    // 首先由本节点，子节点以及属性等信息形成一个XML文档结构对象；
    QDomDocument domDocument("");
    QDomElement rootElement = d->createDomElement(domDocument, this);

    domDocument.appendChild(rootElement);

    // 然后将此文档结构对象格式化为字符串后返回；
    return domDocument.toString(1);
}

// 升级
bool XmlNode::update(XmlNode* destNode, const XmlNode* srcNode)
{
    QStringList srcKeys = srcNode->attributes();
    QStringList destKeys = destNode->attributes();

    foreach (QString key, destKeys)
    {
        if (srcKeys.contains(key))
        {
            QString value = srcNode->attribute(key);
            destNode->setAttribute(key, value);
            if (value == "AUTO_CLEAN_CRP_TUBE")
            {
                QString valueTime = srcNode->attribute("value");
                valueTime = QString::number((valueTime.toInt() <  48) ? 48 : ((valueTime.toInt() > 72) ? 72 : valueTime.toInt()));
                destNode->setAttribute("value", valueTime);
            }
        }
    }

    return true;
}