#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_


#include <QLocale>
#include <QStringList>

#include "liblanguage.h"


// ”Ô—‘
namespace Language
{
    // ”Ô—‘º”‘ÿ
    LANGUAGE_EXPORT bool load(const QString& fileName);

    // ªÒ»°◊÷∑˚¥Æ
    LANGUAGE_EXPORT QString getString(const QString& ids);
};


#endif // _LANGUAGE_H_