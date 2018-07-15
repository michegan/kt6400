#ifndef _LOGIN_WIN_H_
#define _LOGIN_WIN_H_


#include "funcwin.h"

#include "ui_loginwin.h"


// 主界面
class LoginWin : public FuncWin
{
    Q_OBJECT

public:
    LoginWin(QWidget* parent = 0);
    virtual ~LoginWin();

protected:
    // 界面字符串
    virtual void setWindowText();

protected:
    // 事件处理
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // 按钮点击
    void onBtnOkClicked();

private:
    Ui::LoginWin ui;
};


#endif // _LOGIN_WIN_H_
