#ifndef _UI_VARIANTS_H_
#define _UI_VARIANTS_H_


#include <QHash>
#include <QVariant>
#include <QStringList>


// UI����
namespace UIVariants
{
    // ��ȡ����
    int intVariant(const QString& name);
    float floatVariant(const QString& name);
    QString strVariant(const QString& name);

    QVariant getVariant(const QString& name);

    // ���ı���
    void setVariant(const QString& name, const QVariant& value);
};


#endif // _UI_VARIANTS_H_