#ifndef _LOGIN_WIN_H_
#define _LOGIN_WIN_H_


#include "funcwin.h"

#include "ui_loginwin.h"


// ������
class LoginWin : public FuncWin
{
    Q_OBJECT

public:
    LoginWin(QWidget* parent = 0);
    virtual ~LoginWin();

protected:
    // �����ַ���
    virtual void setWindowText();

protected:
    // �¼�����
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // ��ť���
    void onBtnOkClicked();

private:
    Ui::LoginWin ui;
};


#endif // _LOGIN_WIN_H_
