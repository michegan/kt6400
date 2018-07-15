#ifndef _ENGLISH_KEY_BOARD_H_
#define _ENGLISH_KEY_BOARD_H_


#include "keyboard.h"


// Ó¢ÓïÖ÷Èí¼üÅÌ
class EnglishMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishMainKeyBoard();
    virtual ~EnglishMainKeyBoard();
};


// Ó¢ÓïÊı×ÖÈí¼üÅÌ
class EnglishNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishNumberKeyBoard();
    virtual ~EnglishNumberKeyBoard();
};


// Ó¢Óï·ûºÅÈí¼üÅÌ
class EnglishPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    EnglishPunctionKeyBoard();
    virtual ~EnglishPunctionKeyBoard();
};


#endif // _ENGLISH_KEY_BOARD_H_