#ifndef _UI_VARIANTS_H_
#define _UI_VARIANTS_H_


#include <QHash>
#include <QVariant>
#include <QStringList>


// UI变量
namespace UIVariants
{
    // 获取变量
    int intVariant(const QString& name);
    float floatVariant(const QString& name);
    QString strVariant(const QString& name);

    QVariant getVariant(const QString& name);

    // 更改变量
    void setVariant(const QString& name, const QVariant& value);
};


#endif // _UI_VARIANTS_H_