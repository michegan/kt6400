#include <QtDebug>

#include "uivariants.h"


// UI����
namespace UIVariants
{
    // ���еı���
    static QHash<QString, QVariant> variants;

    // ��ȡ����
    int intVariant(const QString& name)
    {
        QString value = UIVariants::strVariant(name);
        return value.toInt();
    }

    float floatVariant(const QString& name)
    {
        QString value = UIVariants::strVariant(name);
        return value.toFloat();
    }

    QString strVariant(const QString& name)
    {
        QVariant variant = UIVariants::getVariant(name);
        return variant.toString();
    }

    QVariant getVariant(const QString& name)
    {
        return variants.value(name);
    }

    // ���ı���
    void setVariant(const QString& name, const QVariant& value)
    {
        if (variants.contains(name))
        {
            variants[name] = value;
        }
        else
        {
            variants.insert(name, value);
        }
    }
}