#ifndef _TIME_LINEEDIT_H_
#define _TIME_LINEEDIT_H_


#include <QTime>

#include "multilineedit.h"


// 时间编辑框控件
class WIDGET_EXPORT TimeLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    TimeLineEdit(QWidget* parent = 0);
    virtual ~TimeLineEdit();

    // 有效性
    bool isNull();
    bool isValid();

    // 时间
    QTime time();
    void setTime(const QTime& time);

private:
    // 时间
    int hour();
    int minute();

    // 时间控件
    DigitLineEdit* hourEdit();
    DigitLineEdit* minuteEdit();
};


#endif // _TIME_LINEEDIT_H_