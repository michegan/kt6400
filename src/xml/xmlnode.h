#ifndef _XML_NODE_H_
#define _XML_NODE_H_


#include <QStringList>

#include "libxml.h"


class XmlNodePrivate;


// Xml�ڵ�
class XML_EXPORT XmlNode
{
public:
    XmlNode();
    XmlNode(const QString& name);
    XmlNode(const XmlNode& other);
    virtual ~XmlNode();

     // �ڵ�����
    QString name() const;
    void setName(const QString& name);

    // �򱾽ڵ�����ӽڵ㣬����һ���µĽڵ㣬������ӵ����ڵ���ӽڵ�������
    XmlNode* appendChild(XmlNode* child);
    XmlNode* appendChild(const QString& name);

    // �򱾽ڵ��������
    bool appendAttribute(const QString& attrName, int attrValue);
    bool appendAttribute(const QString& attrName, float attrValue);
    bool appendAttribute(const QString& attrName, const QString& attrValue);

    // һ�λ�ȡ���е��ӽڵ�
    QList<XmlNode*> childs() const;

    // ȡ��һ���ֽڵ�
    XmlNode* firstChild() const;

    // ȡָ����ĳ���ӽڵ�
    XmlNode* child(const QString& id) const;

    // �򱾽ڵ��������
    bool setAttribute(const QString& attrName, int attrValue);
    bool setAttribute(const QString& attrName, bool attrValue);
    bool setAttribute(const QString& attrName, float attrValue);
    bool setAttribute(const QString& attrName, const QString& attrValue);

    // ��ȡ���еĽڵ���������
    QStringList attributes() const;

    // ��ȡָ�����Ƶ�����ֵ�������������ִ�Сд
    QString attribute(const QString& attrName) const;

    int intAttribute(const QString& attrName) const;
    bool boolAttribute(const QString& attrName) const;
    float floatAttribute(const QString& attrName) const;

    // �˽ڵ㼰�����е��ӽڵ㣬��ʽ���γ�һ��XML��ʽ���ַ���
    QString toString() const;

public:
    // �ڵ���������ͬ��������ֵ������
    static bool update(XmlNode* destNode, const XmlNode* srcNode);

private:
    XmlNodePrivate* d;
    friend class XmlNodePrivate;
};


#endif // _IPU_PROTOCOL_NODE_H_