#ifndef _DATETIME_H_
#define _DATETIME_H_


#include <QString>
#include <QDateTime>

#include "libcommon.h"


// ����ʱ�䣨ʵ�ֶ�����ʱ���ͳһ��ʽ������
namespace DateTime
{
    // ����ʱ���ʽ
    COMMON_EXPORT QString dateFormat();
    COMMON_EXPORT void setDateFormat(const QString& format);


    // ����ʱ���ʽ�����ַ���->����ʱ�䣬��ǰ��ʽ��
    COMMON_EXPORT QDate dateFromStringC(const QString& date);
    COMMON_EXPORT QTime timeFromStringC(const QString& time);

    COMMON_EXPORT QDateTime datetimeFromStringC(const QString& datetime);

    // ����ʱ���ʽ�����ַ���->����ʱ�䣬Ĭ�ϸ�ʽ��
    COMMON_EXPORT QDate dateFromStringD(const QString& date);
    COMMON_EXPORT QTime timeFromStringD(const QString& time);

    COMMON_EXPORT QDateTime datetimeFromStringD(const QString& datetime);


    // ����ʱ���ʽ��������ʱ��->�ַ�������ǰ��ʽ��
    COMMON_EXPORT QString dateToStringC(const QDate& date);
    COMMON_EXPORT QString timeToStringC(const QTime& time);

    COMMON_EXPORT QString datetimeToStringC(const QDateTime& datetime);
    COMMON_EXPORT QString datetimeToStringC(const QDate& date, const QTime& time);

    // ����ʱ���ʽ��������ʱ��->�ַ�����Ĭ�ϸ�ʽ��
    COMMON_EXPORT QString dateToStringD(const QDate& date);
    COMMON_EXPORT QString timeToStringD(const QTime& time);

    COMMON_EXPORT QString datetimeToStringD(const QDateTime& datetime);
    COMMON_EXPORT QString datetimeToStringD(const QDate& date, const QTime& time);
};


#endif // _DATETIME_H_