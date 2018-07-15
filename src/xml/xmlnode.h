#ifndef _XML_NODE_H_
#define _XML_NODE_H_


#include <QStringList>

#include "libxml.h"


class XmlNodePrivate;


// Xml节点
class XML_EXPORT XmlNode
{
public:
    XmlNode();
    XmlNode(const QString& name);
    XmlNode(const XmlNode& other);
    virtual ~XmlNode();

     // 节点名称
    QString name() const;
    void setName(const QString& name);

    // 向本节点添加子节点，创建一个新的节点，将其添加到本节点的子节点链表中
    XmlNode* appendChild(XmlNode* child);
    XmlNode* appendChild(const QString& name);

    // 向本节点添加属性
    bool appendAttribute(const QString& attrName, int attrValue);
    bool appendAttribute(const QString& attrName, float attrValue);
    bool appendAttribute(const QString& attrName, const QString& attrValue);

    // 一次获取所有的子节点
    QList<XmlNode*> childs() const;

    // 取第一个字节点
    XmlNode* firstChild() const;

    // 取指定的某个子节点
    XmlNode* child(const QString& id) const;

    // 向本节点添加属性
    bool setAttribute(const QString& attrName, int attrValue);
    bool setAttribute(const QString& attrName, bool attrValue);
    bool setAttribute(const QString& attrName, float attrValue);
    bool setAttribute(const QString& attrName, const QString& attrValue);

    // 获取所有的节点属性名称
    QStringList attributes() const;

    // 获取指定名称的属性值，属性名称区分大小写
    QString attribute(const QString& attrName) const;

    int intAttribute(const QString& attrName) const;
    bool boolAttribute(const QString& attrName) const;
    float floatAttribute(const QString& attrName) const;

    // 此节点及其所有的子节点，格式化形成一个XML格式的字符串
    QString toString() const;

public:
    // 节点升级（相同属性属性值拷贝）
    static bool update(XmlNode* destNode, const XmlNode* srcNode);

private:
    XmlNodePrivate* d;
    friend class XmlNodePrivate;
};


#endif // _IPU_PROTOCOL_NODE_H_