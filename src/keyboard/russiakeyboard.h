#ifndef _RUSSIA_KEY_BOARD_H_
#define _RUSSIA_KEY_BOARD_H_


#include "keyboard.h"


// �����������
class RussiaMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaMainKeyBoard();
    virtual ~RussiaMainKeyBoard();
};


// �������������
class RussiaNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaNumberKeyBoard();
    virtual ~RussiaNumberKeyBoard();
};


// ������������
class RussiaPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaPunctionKeyBoard();
    virtual ~RussiaPunctionKeyBoard();
};


#endif // _RUSSIA_KEY_BOARD_H_