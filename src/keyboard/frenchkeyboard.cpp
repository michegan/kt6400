#include "keybutton.h"
#include "frenchkeyboard.h"


// 法语主软键盘
FrenchMainKeyBoard::FrenchMainKeyBoard()
    : KeyBoard(Qt::Key_F1)
{
    // 第一行
    this->newLine(10);

    this->addChrButton(0x00C0); // à
    this->addChrButton(0x00C2); // ?
    this->addChrButton(0x00C8); // è
    this->addChrButton(0x00C9); // é
    this->addChrButton(0x00CA); // ê
    this->addChrButton(0x00CB); // ?
    this->addChrButton(0x00CE); // ?
    this->addChrButton(0x00CF); // ?
    this->addChrButton(0x00D4); // ?
    this->addChrButton(0x00D6); // ?
    this->addChrButton(0x00D9); // ù
    this->addChrButton(0x00DB); // ?

    // 第二行
    this->newLine(35);

    this->addChrButton(Qt::Key_Q);
    this->addChrButton(Qt::Key_W);
    this->addChrButton(Qt::Key_E);
    this->addChrButton(Qt::Key_R);
    this->addChrButton(Qt::Key_T);
    this->addChrButton(Qt::Key_Y);
    this->addChrButton(Qt::Key_U);
    this->addChrButton(Qt::Key_I);
    this->addChrButton(Qt::Key_O);
    this->addChrButton(Qt::Key_P);
    this->addChrButton(0x00C7); // ?

    // 第三行
    this->newLine(60);

    this->addChrButton(Qt::Key_A);
    this->addChrButton(Qt::Key_S);
    this->addChrButton(Qt::Key_D);
    this->addChrButton(Qt::Key_F);
    this->addChrButton(Qt::Key_G);
    this->addChrButton(Qt::Key_H);
    this->addChrButton(Qt::Key_J);
    this->addChrButton(Qt::Key_K);
    this->addChrButton(Qt::Key_L);
    this->addChrButton(0x0152); // ?

    // 第四行
    this->newLine(10);

    this->addImageButton(Qt::Key_CapsLock, "capslock", 78);
    this->addChrButton(Qt::Key_Z);
    this->addChrButton(Qt::Key_X);
    this->addChrButton(Qt::Key_C);
    this->addChrButton(Qt::Key_V);
    this->addChrButton(Qt::Key_B);
    this->addChrButton(Qt::Key_N);
    this->addChrButton(Qt::Key_M);
    this->addChrButton(0x00C6); // ?
    this->addChrButton(0x20AC); // �
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // 第五行
    this->newLine(10);

    this->addImageButton(Qt::Key_F2, "number", 78);
    this->addImageButton(Qt::Key_Space, "space", 391);
    this->addImageButton(Qt::Key_F3, "punction", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // 设置窗口大小
    setFixedSize(582 + 114, 216 + 53);

    // 对一些按钮进行特殊处理
    // 大写按钮
    KeyButton* keyButton = this->button(Qt::Key_CapsLock);
    if (keyButton)
    {
        keyButton->setCheckable(true);
    }
}

FrenchMainKeyBoard::~FrenchMainKeyBoard()
{

}


// 法语数字软键盘
FrenchNumberKeyBoard::FrenchNumberKeyBoard()
    : KeyBoard(Qt::Key_F2)
{
    // 第一行
    this->newLine(10);

    this->addChrButton(Qt::Key_1); // 1
    this->addChrButton(Qt::Key_2); // 2
    this->addChrButton(Qt::Key_3); // 3
    this->addChrButton(Qt::Key_4); // 4
    this->addChrButton(Qt::Key_5); // 5
    this->addChrButton(Qt::Key_6); // 6
    this->addChrButton(Qt::Key_7); // 7
    this->addChrButton(Qt::Key_8); // 8
    this->addChrButton(Qt::Key_9); // 9
    this->addChrButton(Qt::Key_0); // 0

    // 第二行
    this->newLine(39);

    this->addChrButton(Qt::Key_Plus); // +
    this->addChrButton(Qt::Key_Minus); // -
    this->addChrButton(Qt::Key_Asterisk); // *
    this->addChrButton(Qt::Key_Slash); // /
    this->addChrButton(Qt::Key_Equal); // =
    this->addChrButton(Qt::Key_Percent); // %
    this->addChrButton(Qt::Key_Less); // <
    this->addChrButton(Qt::Key_Greater); // >
    this->addChrButton(Qt::Key_Period); // .

    // 第三行
    this->newLine(10);

    this->addImageButton(0x2026, "dots", 78);

    this->addChrButton(Qt::Key_Comma); // ,
    this->addChrButton(Qt::Key_Apostrophe); // '
    this->addChrButton(Qt::Key_QuoteDbl); // "
    this->addChrButton(Qt::Key_ParenLeft); // (
    this->addChrButton(Qt::Key_ParenRight); // )
    this->addChrButton(Qt::Key_Underscore); // _
    this->addChrButton(Qt::Key_At); // @
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // 第四行
    this->newLine(10);

    this->addImageButton(Qt::Key_F1, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_F3, "punction", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // 设置窗口大小
    setFixedSize(582, 216);
}

FrenchNumberKeyBoard::~FrenchNumberKeyBoard()
{

}


// 法语符号软键盘
FrenchPunctionKeyBoard::FrenchPunctionKeyBoard()
    : KeyBoard(Qt::Key_F3)
{
    // 第一行
    this->newLine(10);

    this->addChrButton(Qt::Key_AsciiTilde); // ~
    this->addChrButton(Qt::Key_Exclam); // !
    this->addChrButton(Qt::Key_At); // @
    this->addChrButton(Qt::Key_NumberSign); // #
    this->addChrButton(Qt::Key_Dollar); // $
    this->addChrButton(Qt::Key_Percent); // %
    this->addChrButton(Qt::Key_AsciiCircum); // ^
    this->addChrButton(Qt::Key_Ampersand); // &
    this->addChrButton(Qt::Key_Asterisk); // *
    this->addChrButton(0x20AC); // �

    // 第二行
    this->newLine(39);

    this->addChrButton(Qt::Key_Comma); // ,
    this->addChrButton(Qt::Key_Period); // .
    this->addChrButton(Qt::Key_Colon); // :
    this->addChrButton(Qt::Key_Semicolon); // ;
    this->addChrButton(Qt::Key_Slash); // /
    this->addChrButton(Qt::Key_Backslash); // '\'
    this->addChrButton(Qt::Key_Bar); // |
    this->addChrButton(Qt::Key_Less); // <
    this->addChrButton(Qt::Key_Greater); // >

    // 第三行
    this->newLine(10);

    this->addImageButton(0x2026, "dots", 78);
    this->addChrButton(Qt::Key_ParenLeft); // (
    this->addChrButton(Qt::Key_ParenRight); // )
    this->addChrButton(Qt::Key_BracketLeft); // [
    this->addChrButton(Qt::Key_BracketRight); // ]
    this->addChrButton(Qt::Key_BraceLeft); // {
    this->addChrButton(Qt::Key_BraceRight); // }
    this->addChrButton(Qt::Key_Question); // ?
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // 第四行
    this->newLine(10);

    this->addImageButton(Qt::Key_F1, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_F2, "number", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // 设置窗口大小
    setFixedSize(582, 216);
}

FrenchPunctionKeyBoard::~FrenchPunctionKeyBoard()
{

}