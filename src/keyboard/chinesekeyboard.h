#ifndef _CHINESE_KEY_BOARD_H_
#define _CHINESE_KEY_BOARD_H_


#include "keyboard.h"

class PinYin;
class ChineseMainKeyBoardPrivate;


// 汉语主软键盘（可切换到英文）
class ChineseMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseMainKeyBoard();
    virtual ~ChineseMainKeyBoard();

    // 关联输入法
    PinYin* ime();
    void setIme(PinYin* ime);

    // 清除输入
    virtual void clear();

    // 按键处理
    virtual bool onKeyReleaseEvent(int key);

    // CAPS状态
    virtual bool capslock() const;

private slots:
    // 输入按键
    void onButtonClicked(int chr);

    // 输入结束
    void onInputFinished(const QString& text);

private:
    ChineseMainKeyBoardPrivate* d;
};


// 汉语字符软键盘（可切换到英文）
class ChineseLetterKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetterKeyBoard();
    virtual ~ChineseLetterKeyBoard();
};


// 汉语字符软键盘（可切换到中文）
class ChineseLetter1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetter1KeyBoard();
    virtual ~ChineseLetter1KeyBoard();
};


// 汉语字符软键盘（无中英文切换）
class ChineseLetter2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetter2KeyBoard();
    virtual ~ChineseLetter2KeyBoard();
};


// 汉语数字软键盘（可切换到英文）
class ChineseNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumberKeyBoard();
    virtual ~ChineseNumberKeyBoard();

    // 按键处理
    virtual bool onKeyReleaseEvent(int key);
};


// 汉语数字软键盘（可切换到中文）
class ChineseNumber1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumber1KeyBoard();
    virtual ~ChineseNumber1KeyBoard();
};


// 汉语数字软键盘（无中英文切换）
class ChineseNumber2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumber2KeyBoard();
    virtual ~ChineseNumber2KeyBoard();
};


// 汉语符号软键盘（可切换到英文）
class ChinesePunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunctionKeyBoard();
    virtual ~ChinesePunctionKeyBoard();

    // 按键处理
    virtual bool onKeyReleaseEvent(int key);
};


// 汉语符号软键盘（可切换到中文）
class ChinesePunction1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunction1KeyBoard();
    virtual ~ChinesePunction1KeyBoard();
};


// 汉语符号软键盘（无中英文切换）
class ChinesePunction2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunction2KeyBoard();
    virtual ~ChinesePunction2KeyBoard();
};


#endif // _CHINESE_KEY_BOARD_H_