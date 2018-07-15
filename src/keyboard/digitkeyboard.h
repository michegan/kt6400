#ifndef _DIGIT_KEY_BOARD_H_
#define _DIGIT_KEY_BOARD_H_


#include "keyboard.h"


// Êý×ÖÈí¼üÅÌ
class DigitKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    DigitKeyBoard(int chr = Qt::Key_Period);
    virtual ~DigitKeyBoard();
};


#endif // _DIGIT_KEY_BOARD_H_