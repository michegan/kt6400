#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_


#include <QLocale>
#include <QStringList>

#include "liblanguage.h"


// ����
namespace Language
{
    // ���Լ���
    LANGUAGE_EXPORT bool load(const QString& fileName);

    // ��ȡ�ַ���
    LANGUAGE_EXPORT QString getString(const QString& ids);
};


#endif // _LANGUAGE_H_