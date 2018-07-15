#ifndef _DIGIT_LINEEDIT_H_
#define _DIGIT_LINEEDIT_H_


#include "lineedit.h"

class DigitLineEditPrivate;


// 数字编辑框控件
class WIDGET_EXPORT DigitLineEdit : public LineEdit
{
    Q_OBJECT

public:
    DigitLineEdit(QWidget* parent = 0);
    virtual ~DigitLineEdit();

    // 设置值
    double value() const;
    void setValue(double value);

    // 设置范围
    void setRange(double lower, double upper);

    // 设置格式
    int digits() const;
    void setFormat(int integers, int decimals = 0);

public:
    // 是否有效
    virtual bool isValid();

protected:
    // 按键响应
    virtual void keyPressEvent(QKeyEvent* event);

private:
    // 范围
    double lower;
    double upper;

    // 格式
    int integers;
    int decimals;
};


#endif // _DIGIT_LINEEDIT_H_