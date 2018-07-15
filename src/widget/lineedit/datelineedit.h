#ifndef _DATE_LINEEDIT_H_
#define _DATE_LINEEDIT_H_


#include <QDate>

#include "multilineedit.h"


// 日期编辑框控件
class WIDGET_EXPORT DateLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    DateLineEdit(QWidget* parent = 0);
    virtual ~DateLineEdit();

    // 有效性
    bool isNull();
    bool isValid();

    // 日期
    QDate date();
    void setDate(const QDate& date);

    // 日期格式
    void setDateFormat(const QString& format);

private:
    // 日期
    int year();
    int month();
    int day();

    // 日期控件
    DigitLineEdit* yearEdit();
    DigitLineEdit* monthEdit();
    DigitLineEdit* dayEdit();

private:
    // 日期格式
    QString format;
};


#endif // _DATE_LINEEDIT_H_