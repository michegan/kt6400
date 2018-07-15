#ifndef _MENU_WIN_H_
#define _MENU_WIN_H_


#include "funcwin.h"

#include "ui_menuwin.h"


// ������
class MenuWin : public FuncWin
{
    Q_OBJECT

public:
    MenuWin(QWidget* parent = 0);
    virtual ~MenuWin();

protected:
    // �����ַ���
    virtual void setWindowText();

protected:
    // �¼�����
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // ��ť���
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
