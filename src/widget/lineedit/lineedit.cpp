#include "lineedit.h"


LineEdit::LineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    // Ĭ�ϳߴ�
    this->resize(100, 30);
}

LineEdit::~LineEdit()
{

}

// �Ƿ���Ч
bool LineEdit::isValid()
{
    // Ĭ�����������κ��ַ�
    return true;
}

// ������Ӧ
void LineEdit::keyPressEvent(QKeyEvent* event)
{
    QLineEdit::keyPressEvent(event);
}