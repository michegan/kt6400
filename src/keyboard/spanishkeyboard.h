#ifndef _SPANISH_KEY_BOARD_H_
#define _SPANISH_KEY_BOARD_H_


#include "keyboard.h"


// ���������������
class SpanishMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishMainKeyBoard();
    virtual ~SpanishMainKeyBoard();
};


// �����������������
class SpanishNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishNumberKeyBoard();
    virtual ~SpanishNumberKeyBoard();
};


// ����������������
class SpanishPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishPunctionKeyBoard();
    virtual ~SpanishPunctionKeyBoard();
};


#endif // _SPANISH_KEY_BOARD_H_