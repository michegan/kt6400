#ifndef _XML_H_
#define _XML_H_


#include <QMap>
#include <QString>

#include "libxml.h"


class XmlNode;
class XmlPrivate;


// ����
#define ATTR_ID                     ("id")
#define ATTR_VALUE                  ("value")


// Xml�ļ�
class XML_EXPORT Xml
{
public:
    Xml(const QString& fileName);
    virtual ~Xml();

    // ����
    bool load();

    // ����д��
    bool save();

    // �ļ����
    bool check();

    // �ָ�Ĭ������
    bool makeDefault();

    // ȫ���ڵ�
    QMap<QString, XmlNode*> allNodes();
    QMap<QString, XmlNode*> allNodes(const QString& path, XmlNode* rootNode);

    // �ؼ��֣���һ���ӽڵ㣩
    QStringList keys1();
    // �ؼ��֣��ڶ����ӽڵ㣩
    QStringList keys2(const QString& key1);

    // ��ȡֵ���ڶ����ӽڵ㣩
    float getFloatValue2(const QString& key1, const QString& key2);
    QString getTextValue2(const QString& key1, const QString& key2);

    float getFloatAttribute2(const QString& key1, const QString& key2, const QString& attribute);
    QString getTextAttribute2(const QString& key1, const QString& key2, const QString& attribute);

    // ����ֵ���ڶ����ӽڵ㣩
    bool setFloatValue2(const QString& key1, const QString& key2, float value);
    bool setTextValue2(const QString& key1, const QString& key2, const QString& value);

    bool setTextAttribute2(const QString& key1, const QString& key2, const QString& value, const QString& attribute);

public:
    // ���ڵ�
    XmlNode* rootNode();

    // ȡ�ڵ�
    XmlNode* getNode1(const QString& key1);
    XmlNode* getNode2(const QString& key1, const QString& key2);

    XmlNode* getNode(const QStringList& keys);
    XmlNode* getNode(XmlNode* rootNode, const QString& key);

public:
    // XML�ļ�����
    static bool update(const QString& destFileName, const QString& srcFileName);
    static bool update(QMap<QString, XmlNode*>& destNodes, const QMap<QString, XmlNode*>& srcNodes);

private:
    XmlPrivate* d;
};


#endif // _XML_H_