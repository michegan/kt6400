#include <QKeyEvent>

#include "datetime.h"
#include "datelineedit.h"
#include "digitlineedit.h"


// 分段数
#define NUM_OF_SECTIONS     (3)

// 其他日期格式
#define OTHER_FORMAT        ("dd-MM-yyyy")


DateLineEdit::DateLineEdit(QWidget* parent)
    : MultiLineEdit(NUM_OF_SECTIONS, "-", parent)
{
    this->setDateFormat(DateTime::dateFormat());
}

DateLineEdit::~DateLineEdit()
{

}

// 有效性
bool DateLineEdit::isNull()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();

    return (year < 0 && month < 0 && day < 0);
}

bool DateLineEdit::isValid()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();

    if (year < 0 && month < 0 && day < 0)
    {
        return true;
    }
    else
    {
        if (1900 <= year && year <= 2036)
        {
            return QDate::isValid(year, month, day);
        }
        else
        {
            return false;
        }
    }
}

// 日期
QDate DateLineEdit::date()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();

    return QDate(year, month, day);
}

void DateLineEdit::setDate(const QDate& date)
{
    // 年
    DigitLineEdit* lineEdit = this->lineEdit(0);
    lineEdit->setValue(date.year());

    // 月
    lineEdit = this->lineEdit(1);
    lineEdit->setValue(date.month());

    // 日
    lineEdit = this->lineEdit(2);
    lineEdit->setValue(date.day());
}

// 日期格式
void DateLineEdit::setDateFormat(const QString& format)
{
    // 保存格式
    this->format = format;

    // 年
    DigitLineEdit* lineEdit = this->yearEdit();
    lineEdit->setRange(1900, 2036);
    lineEdit->setFormat(4, 0);
    lineEdit->setPlaceholderText("yyyy");

    // 月
    lineEdit = this->monthEdit();
    lineEdit->setRange(1, 12);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("mm");

    // 日
    lineEdit = this->dayEdit();
    lineEdit->setRange(1, 31);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("dd");
}

// 日期
int DateLineEdit::year()
{
    DigitLineEdit* lineEdit = this->yearEdit();
    return lineEdit->value();
}

int DateLineEdit::month()
{
    DigitLineEdit* lineEdit = this->monthEdit();
    return lineEdit->value();
}

int DateLineEdit::day()
{
    DigitLineEdit* lineEdit = this->dayEdit();
    return lineEdit->value();
}

// 日期控件
DigitLineEdit* DateLineEdit::yearEdit()
{
    if (this->format == OTHER_FORMAT)
    {
        return this->lineEdit(2);
    }
    else
    {
        return this->lineEdit(0);
    }
}

DigitLineEdit* DateLineEdit::monthEdit()
{
    return this->lineEdit(1);
}

DigitLineEdit* DateLineEdit::dayEdit()
{
    if (this->format == OTHER_FORMAT)
    {
        return this->lineEdit(0);
    }
    else
    {
        return this->lineEdit(2);
    }
}