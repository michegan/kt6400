#ifndef _SPANISH_KEY_BOARD_H_
#define _SPANISH_KEY_BOARD_H_


#include "keyboard.h"


// Î÷°àÑÀÓïÖ÷Èí¼üÅÌ
class SpanishMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishMainKeyBoard();
    virtual ~SpanishMainKeyBoard();
};


// Î÷°àÑÀÓïÊı×ÖÈí¼üÅÌ
class SpanishNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishNumberKeyBoard();
    virtual ~SpanishNumberKeyBoard();
};


// Î÷°àÑÀÓï·ûºÅÈí¼üÅÌ
class SpanishPunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    SpanishPunctionKeyBoard();
    virtual ~SpanishPunctionKeyBoard();
};


#endif // _SPANISH_KEY_BOARD_H_