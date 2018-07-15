#ifndef _XML_H_
#define _XML_H_


#include <QMap>
#include <QString>

#include "libxml.h"


class XmlNode;
class XmlPrivate;


// 属性
#define ATTR_ID                     ("id")
#define ATTR_VALUE                  ("value")


// Xml文件
class XML_EXPORT Xml
{
public:
    Xml(const QString& fileName);
    virtual ~Xml();

    // 加载
    bool load();

    // 保存写入
    bool save();

    // 文件检测
    bool check();

    // 恢复默认配置
    bool makeDefault();

    // 全部节点
    QMap<QString, XmlNode*> allNodes();
    QMap<QString, XmlNode*> allNodes(const QString& path, XmlNode* rootNode);

    // 关键字（第一层子节点）
    QStringList keys1();
    // 关键字（第二层子节点）
    QStringList keys2(const QString& key1);

    // 获取值（第二层子节点）
    float getFloatValue2(const QString& key1, const QString& key2);
    QString getTextValue2(const QString& key1, const QString& key2);

    float getFloatAttribute2(const QString& key1, const QString& key2, const QString& attribute);
    QString getTextAttribute2(const QString& key1, const QString& key2, const QString& attribute);

    // 更新值（第二层子节点）
    bool setFloatValue2(const QString& key1, const QString& key2, float value);
    bool setTextValue2(const QString& key1, const QString& key2, const QString& value);

    bool setTextAttribute2(const QString& key1, const QString& key2, const QString& value, const QString& attribute);

public:
    // 根节点
    XmlNode* rootNode();

    // 取节点
    XmlNode* getNode1(const QString& key1);
    XmlNode* getNode2(const QString& key1, const QString& key2);

    XmlNode* getNode(const QStringList& keys);
    XmlNode* getNode(XmlNode* rootNode, const QString& key);

public:
    // XML文件升级
    static bool update(const QString& destFileName, const QString& srcFileName);
    static bool update(QMap<QString, XmlNode*>& destNodes, const QMap<QString, XmlNode*>& srcNodes);

private:
    XmlPrivate* d;
};


#endif // _XML_H_