#ifndef _MENU_WIN_H_
#define _MENU_WIN_H_


#include "funcwin.h"

#include "ui_menuwin.h"


// 主界面
class MenuWin : public FuncWin
{
    Q_OBJECT

public:
    MenuWin(QWidget* parent = 0);
    virtual ~MenuWin();

protected:
    // 界面字符串
    virtual void setWindowText();

protected:
    // 事件处理
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // 按钮点击
    void onBtnCountClicked();
    void onBtnReviewClicked();
    void onBtnQcClicked();
    void onBtnCalibrateClicked();
    void onBtnMaintainClicked();
    void onBtnSelftestClicked();
    void onBtnSetupClicked();
    void onBtnLogOffClicked();
    void onBtnShutdownClicked();

private:
    Ui::MenuWin ui;
};


#endif // _MENU_WIN_H_
