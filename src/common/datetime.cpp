#include "datetime.h"


namespace DateTime
{
    // ����ʱ���ʽ����ǰ��ʽ��
    static QString s_dateFormatC = "yyyy-MM-dd";
    static QString s_timeFormatC = "hh:mm";

    // ����ʱ���ʽ��Ĭ�ϸ�ʽ��
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

    // ����ʱ���ʽ�����ַ���->����ʱ�䣬��ǰ��ʽ��
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

    // ����ʱ���ʽ�����ַ���->����ʱ�䣬Ĭ�ϸ�ʽ��
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

    // ����ʱ���ʽ��������ʱ��->�ַ�������ǰ��ʽ��
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

    // ����ʱ���ʽ��������ʱ��->�ַ�����Ĭ�ϸ�ʽ��
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