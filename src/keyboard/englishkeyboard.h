#ifndef _ENGLISH_KEY_BOARD_H_
#define _ENGLISH_KEY_BOARD_H_


#include "keyboard.h"


// Ӣ���������
class EnglishMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishMainKeyBoard();
    virtual ~EnglishMainKeyBoard();
};


// Ӣ�����������
class EnglishNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishNumberKeyBoard();
    virtual ~EnglishNumberKeyBoard();
};


// Ӣ����������
class EnglishPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishPunctionKeyBoard();
    virtual ~EnglishPunctionKeyBoard();
};


#endif // _ENGLISH_KEY_BOARD_H_