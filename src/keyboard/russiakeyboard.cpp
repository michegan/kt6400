#include "keybutton.h"
#include "russiakeyboard.h"


// 俄语主软键盘
RussiaMainKeyBoard::RussiaMainKeyBoard()
    : KeyBoard(Qt::Key_F1)
{
    // 第一行
    this->newLine(10);

    this->addChrButton(0x0419); // Й
    this->addChrButton(0x0426); // Ц
    this->addChrButton(0x0423); // У
    this->addChrButton(0x041A); // К
    this->addChrButton(0x0415); // Е
    this->addChrButton(0x041D); // Н
    this->addChrButton(0x0413); // Г
    this->addChrButton(0x0428); // Ш
    this->addChrButton(0x0429); // Щ
    this->addChrButton(0x0417); // З
    this->addChrButton(0x0425); // Х
    this->addChrButton(0x044A); // ъ

    // 第二行
    this->newLine(39);

    this->addChrButton(0x0424); // Ф
    this->addChrButton(0x042B); // Ы
    this->addChrButton(0x0412); // В
    this->addChrButton(0x0410); // А
    this->addChrButton(0x041F); // П
    this->addChrButton(0x0440); // Р
    this->addChrButton(0x041E); // О
    this->addChrButton(0x041B); // Л
    this->addChrButton(0x0414); // Д
    this->addChrButton(0x0416); // Ж
    this->addChrButton(0x042D); // Э

    // 第三行
    this->newLine(10);

    this->addImageButton(Qt::Key_CapsLock, "capslock", 78);
    this->addChrButton(0x042F); // Я
    this->addChrButton(0x0427); // Ч
    this->addChrButton(0x0421); // С
    this->addChrButton(0x041C); // М
    this->addChrButton(0x0418); // И
    this->addChrButton(0x0422); // Т
    this->addChrButton(0x044C); // ь
    this->addChrButton(0x0411); // Б
    this->addChrButton(0x042E); // Ю
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // 第四行
    this->newLine(10);

    this->addImageButton(Qt::Key_F2, "number", 78);
    this->addImageButton(Qt::Key_Space, "space", 391);
    this->addImageButton(Qt::Key_F3, "punction", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // 设置窗口大小
    setFixedSize(582 + 114, 216);

    // 对一些按钮进行特殊处理
    // 大写按钮
    KeyButton* keyButton = this->button(Qt::Key_CapsLock);
    if (keyButton)
    {
        keyButton->setCheckable(true);
    }
}

RussiaMainKeyBoard::~RussiaMainKeyBoard()
{

}


// 俄语数字软键盘
RussiaNumberKeyBoard::RussiaNumberKeyBoard()
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

RussiaNumberKeyBoard::~RussiaNumberKeyBoard()
{

}


// 俄语符号软键盘
RussiaPunctionKeyBoard::RussiaPunctionKeyBoard()
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

RussiaPunctionKeyBoard::~RussiaPunctionKeyBoard()
{

}