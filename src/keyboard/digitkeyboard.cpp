#include "digitkeyboard.h"


DigitKeyBoard::DigitKeyBoard(int chr)
    : KeyBoard(Qt::Key_F10)
{
    // 第一行
    this->newLine(10);

    this->addChrButton(Qt::Key_1);
    this->addChrButton(Qt::Key_2);
    this->addChrButton(Qt::Key_3);

    // 第三行
    this->newLine(10);

    this->addChrButton(Qt::Key_4);
    this->addChrButton(Qt::Key_5);
    this->addChrButton(Qt::Key_6);

    // 第四行
    this->newLine(10);

    this->addChrButton(Qt::Key_7);
    this->addChrButton(Qt::Key_8);
    this->addChrButton(Qt::Key_9);

    // 第四行
    this->newLine(10);

    this->addChrButton(Qt::Key_0);
    this->addChrButton(chr);
    this->addImageButton(Qt::Key_Backspace, "backspace", 49);

    // 设置窗口大小
    setFixedSize(183, 216);
}

DigitKeyBoard::~DigitKeyBoard()
{

}