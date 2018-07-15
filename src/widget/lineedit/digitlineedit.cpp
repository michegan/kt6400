#include <qmath.h>
#include <QKeyEvent>

#include "digitlineedit.h"


DigitLineEdit::DigitLineEdit(QWidget* parent)
    : LineEdit(parent), lower(1), upper(99), integers(2), decimals(0)
{
    // 默认尺寸
    this->resize(100, 30);

    // 默认数字键盘
    this->setProperty("SoftKeyBoard", "digit");
}

DigitLineEdit::~DigitLineEdit()
{

}

// 设置值
double DigitLineEdit::value() const
{
    QString text = this->text();

    if (text.isEmpty())
    {
        return -1;
    }
    else
    {
        bool ok = false;
        double value = text.toDouble(&ok);

        return (ok ? value : -1);
    }
}

void DigitLineEdit::setValue(double value)
{
    QString text = (0 <= value ? QString::number(value, 'f', this->decimals) : "");
    this->setText(text);
}

// 设置范围
void DigitLineEdit::setRange(double lower, double upper)
{
    this->lower = lower;
    this->upper = upper;
}

// 设置格式
int DigitLineEdit::digits() const
{
    return (0 < this->decimals ? this->integers + this->decimals + 1 : this->integers);
}

void DigitLineEdit::setFormat(int integers, int decimals)
{
    this->integers = integers;
    this->decimals = decimals;

    // 编辑框最大长度
    this->setMaxLength(this->digits());
}

// 是否有效
bool DigitLineEdit::isValid()
{
    QString text = this->text();

    // 有效性检测
    if (text.isEmpty())
    {
        return true;
    }
    else
    {
        bool ok = false;

        double value = text.toDouble(&ok);
        if (ok)
        {
            ok = (this->lower <= value && value <= this->upper);
        }
        return ok;
    }
    
}

// 按键响应
void DigitLineEdit::keyPressEvent(QKeyEvent* event)
{
    // 基类处理
    LineEdit::keyPressEvent(event);

    // 子类处理
    QString text = this->text();

    int key = event->key();
    switch (key)
    {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        {
            // 允许输入数字键
        }
        break;

    case Qt::Key_Period:
        {
            // 无小数，或者已经有小数点了，删除新录入的小数点
            if (0 == this->decimals)
            {
                backspace(); // 没有小数部分
            }
            else
            {
                int num = text.count(key);
                if (num < 2)
                {
                    // 保留该小数点
                }
                else
                {
                    backspace(); // 只能有1个小数点
                }
            }
        }
        break;

    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        {
            // 响应退格键和删除键
        }
        break;

    default:
        {
            backspace();
        }
        break;
    }
}