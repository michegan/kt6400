#ifndef _FRENCH_KEY_BOARD_H_
#define _FRENCH_KEY_BOARD_H_


#include "keyboard.h"


// ·¨ÓïÖ÷Èí¼üÅÌ
class FrenchMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    FrenchMainKeyBoard();
    virtual ~FrenchMainKeyBoard();
};


// ·¨ÓïÊı×ÖÈí¼üÅÌ
class FrenchNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    FrenchNumberKeyBoard();
    virtual ~FrenchNumberKeyBoard();
};


// ·¨Óï·ûºÅÈí¼üÅÌ
class FrenchPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    FrenchPunctionKeyBoard();
    virtual ~FrenchPunctionKeyBoard();
};


#endif // _FRENCH_KEY_BOARD_H_