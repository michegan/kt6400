#include <QKeyEvent>

#include "timelineedit.h"
#include "digitlineedit.h"


// 分段数
#define NUM_OF_SECTIONS    (2)


TimeLineEdit::TimeLineEdit(QWidget* parent)
    : MultiLineEdit(NUM_OF_SECTIONS, ":", parent)
{
    // 默认尺寸
    this->resize(100, 30);

    // 时
    DigitLineEdit* lineEdit = this->hourEdit();
    lineEdit->setRange(0, 23);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("hh");

    // 分
    lineEdit = this->minuteEdit();
    lineEdit->setRange(0, 59);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("mm");
}

TimeLineEdit::~TimeLineEdit()
{

}

// 有效性
bool TimeLineEdit::isNull()
{
    int hour = this->hour();
    int minute = this->minute();

    return (hour < 0 && minute < 0);
}

bool TimeLineEdit::isValid()
{
    int hour = this->hour();
    int minute = this->minute();

    if (hour < 0 && minute < 0)
    {
        return true;
    }
    else
    {
        return QTime::isValid(hour, minute, 0);
    }
}

// 时间
QTime TimeLineEdit::time()
{
    int hour = this->hour();
    int minute = this->minute();

    return QTime(hour, minute, 0);
}

void TimeLineEdit::setTime(const QTime& time)
{
    // 时
    DigitLineEdit* lineEdit = this->hourEdit();
    lineEdit->setValue(time.hour());

    // 分
    lineEdit = this->minuteEdit();
    lineEdit->setValue(time.minute());
}

// 时间
int TimeLineEdit::hour()
{
    DigitLineEdit* lineEdit = this->hourEdit();
    return lineEdit->value();
}

int TimeLineEdit::minute()
{
    DigitLineEdit* lineEdit = this->minuteEdit();
    return lineEdit->value();
}

// 时间控件
DigitLineEdit* TimeLineEdit::hourEdit()
{
    return this->lineEdit(0);
}

DigitLineEdit* TimeLineEdit::minuteEdit()
{
    return this->lineEdit(1);
}