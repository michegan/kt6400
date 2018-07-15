#ifndef _DATETIME_H_
#define _DATETIME_H_


#include <QString>
#include <QDateTime>

#include "libcommon.h"


// 日期时间（实现对日期时间的统一格式化处理）
namespace DateTime
{
    // 日期时间格式
    COMMON_EXPORT QString dateFormat();
    COMMON_EXPORT void setDateFormat(const QString& format);


    // 日期时间格式化（字符串->日期时间，当前格式）
    COMMON_EXPORT QDate dateFromStringC(const QString& date);
    COMMON_EXPORT QTime timeFromStringC(const QString& time);

    COMMON_EXPORT QDateTime datetimeFromStringC(const QString& datetime);

    // 日期时间格式化（字符串->日期时间，默认格式）
    COMMON_EXPORT QDate dateFromStringD(const QString& date);
    COMMON_EXPORT QTime timeFromStringD(const QString& time);

    COMMON_EXPORT QDateTime datetimeFromStringD(const QString& datetime);


    // 日期时间格式化（日期时间->字符串，当前格式）
    COMMON_EXPORT QString dateToStringC(const QDate& date);
    COMMON_EXPORT QString timeToStringC(const QTime& time);

    COMMON_EXPORT QString datetimeToStringC(const QDateTime& datetime);
    COMMON_EXPORT QString datetimeToStringC(const QDate& date, const QTime& time);

    // 日期时间格式化（日期时间->字符串，默认格式）
    COMMON_EXPORT QString dateToStringD(const QDate& date);
    COMMON_EXPORT QString timeToStringD(const QTime& time);

    COMMON_EXPORT QString datetimeToStringD(const QDateTime& datetime);
    COMMON_EXPORT QString datetimeToStringD(const QDate& date, const QTime& time);
};


#endif // _DATETIME_H_