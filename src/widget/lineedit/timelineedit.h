#ifndef _TIME_LINEEDIT_H_
#define _TIME_LINEEDIT_H_


#include <QTime>

#include "multilineedit.h"


// ʱ��༭��ؼ�
class WIDGET_EXPORT TimeLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    TimeLineEdit(QWidget* parent = 0);
    virtual ~TimeLineEdit();

    // ��Ч��
    bool isNull();
    bool isValid();

    // ʱ��
    QTime time();
    void setTime(const QTime& time);

private:
    // ʱ��
    int hour();
    int minute();

    // ʱ��ؼ�
    DigitLineEdit* hourEdit();
    DigitLineEdit* minuteEdit();
};


#endif // _TIME_LINEEDIT_H_