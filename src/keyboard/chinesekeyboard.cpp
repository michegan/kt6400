#include "pinyin.h"
#include "imebar.h"
#include "keybutton.h"
#include "chinesekeyboard.h"
#include "englishkeyboard.h"
#include "punctionconvert.h"


class ChineseMainKeyBoardPrivate
{
public:
    ChineseMainKeyBoardPrivate();
    ~ChineseMainKeyBoardPrivate();

public:
    // ���뷨
    PinYin* ime;

    // ������
    ImeBar* imeBar;

    // �����
    KeyBoard* keyBoard;
};

ChineseMainKeyBoardPrivate::ChineseMainKeyBoardPrivate()
    : ime(0), imeBar(new ImeBar()), keyBoard(new ChineseLetterKeyBoard())
{

}

ChineseMainKeyBoardPrivate::~ChineseMainKeyBoardPrivate()
{
    delete keyBoard;
}


// ����������̣����л���Ӣ�ģ�
ChineseMainKeyBoard::ChineseMainKeyBoard()
    : KeyBoard(Qt::Key_F1), d(new ChineseMainKeyBoardPrivate())
{
    d->imeBar->setParent(this);
    d->keyBoard->setParent(this);

    // ���沼��
    this->setGeometry(0, 0, 582, 272);

    d->imeBar->setGeometry(0, 0, this->width(), 71);
    d->keyBoard->setGeometry(0, 71, this->width(), d->keyBoard->height());

    // �����źŲ�
    this->connect(d->keyBoard, SIGNAL(clicked(int)), this, SLOT(onButtonClicked(int)));
}

ChineseMainKeyBoard::~ChineseMainKeyBoard()
{
    delete d;
}

// �������뷨
PinYin* ChineseMainKeyBoard::ime()
{
    return d->ime;
}

void ChineseMainKeyBoard::setIme(PinYin* ime)
{
    // ԭ���뷨
    if (d->ime)
    {
        // �Ͽ��źŲ�
        this->disconnect(d->imeBar, SIGNAL(phraseSelected(const QString&)), d->ime, SLOT(onPhraseSelected(const QString&)));

        this->disconnect(d->ime, SIGNAL(inputFinished(const QString&)), this, SLOT(onInputFinished(const QString&)));
        this->disconnect(d->ime, SIGNAL(phrasesChanged(const QStringList&, const QStringList&)), d->imeBar, SLOT(onPhrasesChanged(const QStringList&, const QStringList&)));

        this->disconnect(d->imeBar, SIGNAL(pinyinDisplayRegionFull()), d->ime, SLOT(onPinyinDisplayRegionFull()));
    }

    // ��ǰ���뷨�ָ�Ĭ��ֵ
    d->ime = 0;

    // �����뷨
    if (ime)
    {
        // �����źŲ�
        this->connect(d->imeBar, SIGNAL(phraseSelected(const QString&)), ime, SLOT(onPhraseSelected(const QString&)));

        this->connect(ime, SIGNAL(inputFinished(const QString&)), this, SLOT(onInputFinished(const QString&)));
        this->connect(ime, SIGNAL(phrasesChanged(const QStringList&, const QStringList&)), d->imeBar, SLOT(onPhrasesChanged(const QStringList&, const QStringList&)));

        this->connect(d->imeBar, SIGNAL(pinyinDisplayRegionFull()), ime, SLOT(onPinyinDisplayRegionFull()));
    }

    d->ime = ime;
}

// �������
void ChineseMainKeyBoard::clear()
{
    // ���뷨
    if (d->ime)
    {
        d->ime->clear();
    }

    // ����
    if (d->imeBar)
    {
        d->imeBar->clear();
    }

    // ����
    if (d->keyBoard)
    {
        d->keyBoard->clear();
    }
}

// ��������
bool ChineseMainKeyBoard::onKeyReleaseEvent(int key)
{
    // ���������뷨����
    bool accepted = d->ime->onNewChar(key);

    // ���뷨������ģ�Ȼ��������������
    if (!accepted)
    {
        accepted = d->imeBar->processInput(key);
    }

    // ǰ��������δ����������Ϊ�����Ž��д���
    if (!accepted)
    {
        QString strChPunc = "";
        if (PunctionConvert::convertToChinesePuncForPyInput(key, strChPunc))
        {
            accepted = true;

            // �����ź�
            if (strChPunc.count() == 1)
            {
                emit clicked(strChPunc.at(0).unicode());
            }
            else
            {
                emit clicked(strChPunc);
            }
        }
        else
        {
            accepted = false;
        }
    }

    return accepted;
}

// CAPS״̬
bool ChineseMainKeyBoard::capslock() const
{
    return d->keyBoard->capslock();
}

// ���밴��
void ChineseMainKeyBoard::onButtonClicked(int chr)
{
    // ���޴������뷨�л�����
    if (Qt::Key_F1 <= chr && chr <= Qt::Key_F10)
    {
        // �����ź�
        emit clicked(chr);
        return;
    }

    // ���������뷨����
    bool accepted = d->ime->onNewChar(chr);

    // ���뷨������ģ�Ȼ��������������
    if (!accepted)
    {
        accepted = d->imeBar->processInput(chr);
    }

    // ��δ�����򽻸��ⲿ����
    if (!accepted)
    {
        // �����ź�
        emit clicked(chr);
    }
}

// �������
void ChineseMainKeyBoard::onInputFinished(const QString& text)
{
    // �����ź�
    emit clicked(text);
}


// �����ַ�����̣����л���Ӣ�ģ�
ChineseLetterKeyBoard::ChineseLetterKeyBoard()
    : KeyBoard(0)
{
    // BUG 7961 1104&1001-����̣�������ڵ��༭��/����������ܡ�
    this->setYSpace(5);
    this->setYMargin(7);

    // ��һ��
    this->newLine(10);

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

    // �ڶ���
    this->newLine(39);

    this->addChrButton(Qt::Key_A);
    this->addChrButton(Qt::Key_S);
    this->addChrButton(Qt::Key_D);
    this->addChrButton(Qt::Key_F);
    this->addChrButton(Qt::Key_G);
    this->addChrButton(Qt::Key_H);
    this->addChrButton(Qt::Key_J);
    this->addChrButton(Qt::Key_K);
    this->addChrButton(Qt::Key_L);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_CapsLock, "capslock", 78);
    this->addChrButton(Qt::Key_Z);
    this->addChrButton(Qt::Key_X);
    this->addChrButton(Qt::Key_C);
    this->addChrButton(Qt::Key_V);
    this->addChrButton(Qt::Key_B);
    this->addChrButton(Qt::Key_N);
    this->addChrButton(Qt::Key_M);
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F2, "number", 78);
    this->addImageButton(Qt::Key_Apostrophe, "charb", 49, true); // '
    this->addImageButton(Qt::Key_Space, "space", 222);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F4, "english", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);

    // ��һЩ��ť�������⴦��
    // ��д��ť
    KeyButton* keyButton = this->button(Qt::Key_CapsLock);
    if (keyButton)
    {
        keyButton->setCheckable(true);
    }
}

ChineseLetterKeyBoard::~ChineseLetterKeyBoard()
{

}


// �����ַ�����̣����л������ģ�
ChineseLetter1KeyBoard::ChineseLetter1KeyBoard()
    : KeyBoard(Qt::Key_F4)
{
    // ��һ��
    this->newLine(10);

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

    // �ڶ���
    this->newLine(39);

    this->addChrButton(Qt::Key_A);
    this->addChrButton(Qt::Key_S);
    this->addChrButton(Qt::Key_D);
    this->addChrButton(Qt::Key_F);
    this->addChrButton(Qt::Key_G);
    this->addChrButton(Qt::Key_H);
    this->addChrButton(Qt::Key_J);
    this->addChrButton(Qt::Key_K);
    this->addChrButton(Qt::Key_L);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_CapsLock, "capslock", 78);
    this->addChrButton(Qt::Key_Z);
    this->addChrButton(Qt::Key_X);
    this->addChrButton(Qt::Key_C);
    this->addChrButton(Qt::Key_V);
    this->addChrButton(Qt::Key_B);
    this->addChrButton(Qt::Key_N);
    this->addChrButton(Qt::Key_M);
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F5, "number", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F1, "chinese", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);

    // ��һЩ��ť�������⴦��
    // ��д��ť
    KeyButton* keyButton = this->button(Qt::Key_CapsLock);
    if (keyButton)
    {
        keyButton->setCheckable(true);
    }
}

ChineseLetter1KeyBoard::~ChineseLetter1KeyBoard()
{

}


// �����ַ�����̣�����Ӣ���л���
ChineseLetter2KeyBoard::ChineseLetter2KeyBoard()
    : KeyBoard(Qt::Key_F9)
{
    // ��һ��
    this->newLine(10);

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

    // �ڶ���
    this->newLine(39);

    this->addChrButton(Qt::Key_A);
    this->addChrButton(Qt::Key_S);
    this->addChrButton(Qt::Key_D);
    this->addChrButton(Qt::Key_F);
    this->addChrButton(Qt::Key_G);
    this->addChrButton(Qt::Key_H);
    this->addChrButton(Qt::Key_J);
    this->addChrButton(Qt::Key_K);
    this->addChrButton(Qt::Key_L);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_CapsLock, "capslock", 78);
    this->addChrButton(Qt::Key_Z);
    this->addChrButton(Qt::Key_X);
    this->addChrButton(Qt::Key_C);
    this->addChrButton(Qt::Key_V);
    this->addChrButton(Qt::Key_B);
    this->addChrButton(Qt::Key_N);
    this->addChrButton(Qt::Key_M);
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F8, "number", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_F7, "punction", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // ���ô��ڴ�С
    setFixedSize(582, 216);

    // ��һЩ��ť�������⴦��
    // ��д��ť
    KeyButton* keyButton = this->button(Qt::Key_CapsLock);
    if (keyButton)
    {
        keyButton->setCheckable(true);
    }
}

ChineseLetter2KeyBoard::~ChineseLetter2KeyBoard()
{

}


// ������������̣����л���Ӣ�ģ�
ChineseNumberKeyBoard::ChineseNumberKeyBoard()
    : KeyBoard(Qt::Key_F2)
{
    // ��һ��
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

    // �ڶ���
    this->newLine(39);

    this->addChrButton(0xFF0B); // ��
    this->addChrButton(0xFF0D); // ��
    this->addChrButton(0x00D7); // ��
    this->addChrButton(0x00F7); // ��
    this->addChrButton(0xFF1D); // ��
    this->addChrButton(0xFF05); // ��
    this->addChrButton(0xFF08); // ��
    this->addChrButton(0xFF09); // ��
    this->addChrButton(Qt::Key_Period); // .

    // ������
    this->newLine(10);

    this->addImageButton(0x2026, "dots", 78);
    this->addChrButton(0xFF0C); // ��
    this->addChrButton(0x3001); // ��
    this->addChrButton(0x3002); // ��
    this->addChrButton(0xFF1B); // ��
    this->addChrButton(0xFF1A); // ��
    this->addChrButton(Qt::Key_Less); // <
    this->addChrButton(Qt::Key_Greater); // >
    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F3, "punction", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F4, "english", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChineseNumberKeyBoard::~ChineseNumberKeyBoard()
{

}

// ��������
bool ChineseNumberKeyBoard::onKeyReleaseEvent(int key)
{
    bool accepted = false;
    QString strChPunc = "";
    if (PunctionConvert::convertToChinesePunc(key, strChPunc))
    {
        accepted = true;

        // �����ź�
        if (strChPunc.count() == 1)
        {
            emit clicked(strChPunc.at(0).unicode());
        }
        else
        {
            emit clicked(strChPunc);
        }
    }

    return accepted;
}


// ������������̣����л������ģ�
ChineseNumber1KeyBoard::ChineseNumber1KeyBoard()
    : KeyBoard(Qt::Key_F5)
{
    // ��һ��
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

    // �ڶ���
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

    // ������
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

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F6, "punction", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F1, "chinese", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChineseNumber1KeyBoard::~ChineseNumber1KeyBoard()
{

}


// ������������̣�����Ӣ���л���
ChineseNumber2KeyBoard::ChineseNumber2KeyBoard()
    : KeyBoard(Qt::Key_F8)
{
    // ��һ��
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

    // �ڶ���
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

    // ������
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

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F9, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_F7, "punction", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChineseNumber2KeyBoard::~ChineseNumber2KeyBoard()
{

}


// �����������̣����л���Ӣ�ģ�
ChinesePunctionKeyBoard::ChinesePunctionKeyBoard()
    : KeyBoard(Qt::Key_F3)
{
    // ��һ��
    this->newLine(10);

    this->addChrButton(0xFF5E); // ��
    this->addChrButton(0xFF01); // ��
    this->addChrButton(0xFF20); // ��
    this->addChrButton(0xFF03); // ��
    this->addChrButton(0xFFE5); // ��
    this->addChrButton(0xFF05); // ��
    this->addChrButton(0xFF06); // ��
    this->addChrButton(0x2030); // ��
    this->addChrButton(0x300A); // ��
    this->addChrButton(0x300B); // ��

    // �ڶ���
    this->newLine(39);

    this->addChrButton(0xFF0C); // ��
    this->addChrButton(0x3001); // ��
    this->addChrButton(0x3002); // ��
    this->addChrButton(0x2018); // ��
    this->addChrButton(0x2019); // ��
    this->addChrButton(0x201C); // ��
    this->addChrButton(0x201D); // ��
    this->addChrButton(0xFF0F); // ��
    this->addChrButton(0xFF3C); // ��

    // ������
    this->newLine(10);

    this->addImageButton(0x2026, "dots", 78);

    this->addChrButton(0xFF08); // ��
    this->addChrButton(0xFF09); // ��
    this->addChrButton(0x3010); // ��
    this->addChrButton(0x3011); // ��
    this->addChrButton(0xFF5B); // ��
    this->addChrButton(0xFF5D); // ��
    this->addChrButton(0xFF1F); // ��

    this->addImageButton(Qt::Key_Backspace, "backspace", 78);

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F1, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F4, "english", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChinesePunctionKeyBoard::~ChinesePunctionKeyBoard()
{

}

// ��������
bool ChinesePunctionKeyBoard::onKeyReleaseEvent(int key)
{
    bool accepted = false;
    QString strChPunc = "";
    if (PunctionConvert::convertToChinesePunc(key, strChPunc))
    {
        accepted = true;

        // �����ź�
        if (strChPunc.count() == 1)
        {
            emit clicked(strChPunc.at(0).unicode());
        }
        else
        {
            emit clicked(strChPunc);
        }
    }

    return accepted;
}


// �����������̣����л������ģ�
ChinesePunction1KeyBoard::ChinesePunction1KeyBoard()
    : KeyBoard(Qt::Key_F6)
{
    // ��һ��
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

    // �ڶ���
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

    // ������
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

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F4, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_Close, "close", 49);
    this->addImageButton(Qt::Key_F1, "chinese", 49);
    this->addImageButton(Qt::Key_Enter, "enter", 78);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChinesePunction1KeyBoard::~ChinesePunction1KeyBoard()
{

}


// �����������̣�����Ӣ���л���
ChinesePunction2KeyBoard::ChinesePunction2KeyBoard()
    : KeyBoard(Qt::Key_F7)
{
    // ��һ��
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

    // �ڶ���
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

    // ������
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

    // ������
    this->newLine(10);

    this->addImageButton(Qt::Key_F9, "letter", 78);
    this->addImageButton(Qt::Key_Space, "space", 277);
    this->addImageButton(Qt::Key_F8, "number", 78);
    this->addImageButton(Qt::Key_Enter, "enter", 106);

    // ���ô��ڴ�С
    setFixedSize(582, 216);
}

ChinesePunction2KeyBoard::~ChinesePunction2KeyBoard()
{

}