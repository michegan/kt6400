#include "datetime.h"


namespace DateTime
{
    // 日期时间格式（当前格式）
    static QString s_dateFormatC = "yyyy-MM-dd";
    static QString s_timeFormatC = "hh:mm";

    // 日期时间格式（默认格式）
    static QString s_dateFormatD = "yyyy-MM-dd";
    static QString s_timeFormatD = "hh:mm";


    QString dateFormat()
    {
        return s_dateFormatC;
    }

    void setDateFormat(const QString& format)
    {
        s_dateFormatC = format;
    }

    // 日期时间格式化（字符串->日期时间，当前格式）
    QDate dateFromStringC(const QString& date)
    {
        return QDate::fromString(date, s_dateFormatC);
    }

    QTime timeFromStringC(const QString& time)
    {
        return QTime::fromString(time, s_dateFormatC);
    }

    QDateTime datetimeFromStringC(const QString& datetime)
    {
        return QDateTime::fromString(datetime, s_dateFormatC + " " + s_timeFormatC);
    }

    // 日期时间格式化（字符串->日期时间，默认格式）
    QDate dateFromStringD(const QString& date)
    {
        return QDate::fromString(date, s_dateFormatD);
    }

    QTime timeFromStringD(const QString& time)
    {
        return QTime::fromString(time, s_dateFormatD);
    }

    QDateTime datetimeFromStringD(const QString& datetime)
    {
        return QDateTime::fromString(datetime, s_dateFormatD + " " + s_timeFormatD);
    }

    // 日期时间格式化（日期时间->字符串，当前格式）
    QString dateToStringC(const QDate& date)
    {
        return date.toString(s_dateFormatC);
    }

    QString timeToStringC(const QTime& time)
    {
        return time.toString(s_timeFormatC);
    }

    QString datetimeToStringC(const QDateTime& datetime)
    {
        return DateTime::datetimeToStringC(datetime.date(), datetime.time());
    }

    QString datetimeToStringC(const QDate& date, const QTime& time)
    {
        return DateTime::dateToStringC(date) + " " + DateTime::timeToStringC(time);
    }

    // 日期时间格式化（日期时间->字符串，默认格式）
    QString dateToStringD(const QDate& date)
    {
        return date.toString(s_dateFormatD);
    }

    QString timeToStringD(const QTime& time)
    {
        return time.toString(s_timeFormatD);
    }

    QString datetimeToStringD(const QDateTime& datetime)
    {
        return DateTime::datetimeToStringD(datetime.date(), datetime.time());
    }

    QString datetimeToStringD(const QDate& date, const QTime& time)
    {
        return DateTime::dateToStringD(date) + " " + DateTime::timeToStringD(time);
    }
}