#ifndef _CHINESE_KEY_BOARD_H_
#define _CHINESE_KEY_BOARD_H_


#include "keyboard.h"

class PinYin;
class ChineseMainKeyBoardPrivate;


// ����������̣����л���Ӣ�ģ�
class ChineseMainKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseMainKeyBoard();
    virtual ~ChineseMainKeyBoard();

    // �������뷨
    PinYin* ime();
    void setIme(PinYin* ime);

    // �������
    virtual void clear();

    // ��������
    virtual bool onKeyReleaseEvent(int key);

    // CAPS״̬
    virtual bool capslock() const;

private slots:
    // ���밴��
    void onButtonClicked(int chr);

    // �������
    void onInputFinished(const QString& text);

private:
    ChineseMainKeyBoardPrivate* d;
};


// �����ַ�����̣����л���Ӣ�ģ�
class ChineseLetterKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetterKeyBoard();
    virtual ~ChineseLetterKeyBoard();
};


// �����ַ�����̣����л������ģ�
class ChineseLetter1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetter1KeyBoard();
    virtual ~ChineseLetter1KeyBoard();
};


// �����ַ�����̣�����Ӣ���л���
class ChineseLetter2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseLetter2KeyBoard();
    virtual ~ChineseLetter2KeyBoard();
};


// ������������̣����л���Ӣ�ģ�
class ChineseNumberKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumberKeyBoard();
    virtual ~ChineseNumberKeyBoard();

    // ��������
    virtual bool onKeyReleaseEvent(int key);
};


// ������������̣����л������ģ�
class ChineseNumber1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumber1KeyBoard();
    virtual ~ChineseNumber1KeyBoard();
};


// ������������̣�����Ӣ���л���
class ChineseNumber2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChineseNumber2KeyBoard();
    virtual ~ChineseNumber2KeyBoard();
};


// �����������̣����л���Ӣ�ģ�
class ChinesePunctionKeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunctionKeyBoard();
    virtual ~ChinesePunctionKeyBoard();

    // ��������
    virtual bool onKeyReleaseEvent(int key);
};


// �����������̣����л������ģ�
class ChinesePunction1KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunction1KeyBoard();
    virtual ~ChinesePunction1KeyBoard();
};


// �����������̣�����Ӣ���л���
class ChinesePunction2KeyBoard : public KeyBoard
{
    Q_OBJECT

public:
    ChinesePunction2KeyBoard();
    virtual ~ChinesePunction2KeyBoard();
};


#endif // _CHINESE_KEY_BOARD_H_