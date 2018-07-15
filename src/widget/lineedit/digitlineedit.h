#ifndef _DIGIT_LINEEDIT_H_
#define _DIGIT_LINEEDIT_H_


#include "lineedit.h"

class DigitLineEditPrivate;


// ���ֱ༭��ؼ�
class WIDGET_EXPORT DigitLineEdit : public LineEdit
{
    Q_OBJECT

public:
    DigitLineEdit(QWidget* parent = 0);
    virtual ~DigitLineEdit();

    // ����ֵ
    double value() const;
    void setValue(double value);

    // ���÷�Χ
    void setRange(double lower, double upper);

    // ���ø�ʽ
    int digits() const;
    void setFormat(int integers, int decimals = 0);

public:
    // �Ƿ���Ч
    virtual bool isValid();

protected:
    // ������Ӧ
    virtual void keyPressEvent(QKeyEvent* event);

private:
    // ��Χ
    double lower;
    double upper;

    // ��ʽ
    int integers;
    int decimals;
};


#endif // _DIGIT_LINEEDIT_H_