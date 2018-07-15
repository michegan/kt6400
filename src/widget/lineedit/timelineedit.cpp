#include <QKeyEvent>

#include "timelineedit.h"
#include "digitlineedit.h"


// �ֶ���
#define NUM_OF_SECTIONS    (2)


TimeLineEdit::TimeLineEdit(QWidget* parent)
    : MultiLineEdit(NUM_OF_SECTIONS, ":", parent)
{
    // Ĭ�ϳߴ�
    this->resize(100, 30);

    // ʱ
    DigitLineEdit* lineEdit = this->hourEdit();
    lineEdit->setRange(0, 23);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("hh");

    // ��
    lineEdit = this->minuteEdit();
    lineEdit->setRange(0, 59);
    lineEdit->setFormat(2, 0);
    lineEdit->setPlaceholderText("mm");
}

TimeLineEdit::~TimeLineEdit()
{

}

// ��Ч��
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

// ʱ��
QTime TimeLineEdit::time()
{
    int hour = this->hour();
    int minute = this->minute();

    return QTime(hour, minute, 0);
}

void TimeLineEdit::setTime(const QTime& time)
{
    // ʱ
    DigitLineEdit* lineEdit = this->hourEdit();
    lineEdit->setValue(time.hour());

    // ��
    lineEdit = this->minuteEdit();
    lineEdit->setValue(time.minute());
}

// ʱ��
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

// ʱ��ؼ�
DigitLineEdit* TimeLineEdit::hourEdit()
{
    return this->lineEdit(0);
}

DigitLineEdit* TimeLineEdit::minuteEdit()
{
    return this->lineEdit(1);
}