#ifndef _RUSSIA_KEY_BOARD_H_
#define _RUSSIA_KEY_BOARD_H_


#include "keyboard.h"


// ¶íÓïÖ÷Èí¼üÅÌ
class RussiaMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaMainKeyBoard();
    virtual ~RussiaMainKeyBoard();
};


// ¶íÓïÊı×ÖÈí¼üÅÌ
class RussiaNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaNumberKeyBoard();
    virtual ~RussiaNumberKeyBoard();
};


// ¶íÓï·ûºÅÈí¼üÅÌ
class RussiaPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    RussiaPunctionKeyBoard();
    virtual ~RussiaPunctionKeyBoard();
};


#endif // _RUSSIA_KEY_BOARD_H_