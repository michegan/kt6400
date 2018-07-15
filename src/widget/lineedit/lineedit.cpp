#include "lineedit.h"


LineEdit::LineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    // 默认尺寸
    this->resize(100, 30);
}

LineEdit::~LineEdit()
{

}

// 是否有效
bool LineEdit::isValid()
{
    // 默认允许输入任何字符
    return true;
}

// 按键响应
void LineEdit::keyPressEvent(QKeyEvent* event)
{
    QLineEdit::keyPressEvent(event);
}