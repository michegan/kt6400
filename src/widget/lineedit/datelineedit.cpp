#include <QKeyEvent>

#include "datetime.h"
#include "datelineedit.h"
#include "digitlineedit.h"


// �ֶ���
#define NUM_OF_SECTIONS     (3)

// �������ڸ�ʽ
#define OTHER_FORMAT        ("dd-MM-yyyy")


DateLineEdit::DateLineEdit(QWidget* parent)
    : MultiLineEdit(NUM_OF_SECTIONS, "-", parent)
{
    this->setDateFormat(DateTime::dateFormat());
}

DateLineEdit::~DateLineEdit()
{

}

// ��Ч��
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

// ����
QDate DateLineEdit::date()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();

    return QDate(year, month, day);
}

void DateLineEdit::setDate(const QDate& date)
{
    // ��
    DigitLineEdit* lineEdit = this->lineEdit(0);
    lineEdit->setValue(date.year());

    // ��
    lineEdit = this->lineEdit(1);
    lineEdit->setValue(date.month());

    // ��
    lineEdit = this->lineEdit(2);
    lineEdit->setValue(date.day());
}

// ���ڸ�ʽ
void DateLineEdit::setDateFormat(const QString& format)
{
    // �����ʽ
    this->format = format;

    // ��
    DigitLineEdit* lineEdit = this->yearEdit();
    lineEdit->setRange(1900, 2036);
    lineEdit->setFormat(4, 0);
    lineEdit->setPlaceholderText("yyyy");

    // ��
    lineEdit = this->monthEdit();
    lineEdit->setRange(1, 12);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("mm");

    // ��
    lineEdit = this->dayEdit();
    lineEdit->setRange(1, 31);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("dd");
}

// ����
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

// ���ڿؼ�
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