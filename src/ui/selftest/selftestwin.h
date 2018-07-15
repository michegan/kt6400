#ifndef _SELFTEST_WIN_H_
#define _SELFTEST_WIN_H_


#include "funcwin.h"

#include "ui_selftestwin.h"


// ������
class SelftestWin : public FuncWin
{
    Q_OBJECT

public:
    SelftestWin(QWidget* parent = 0);
    virtual ~SelftestWin();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    void onBtnMotorClicked();
    void onBtnValveClicked();
    void onBtnOtherClicked();
    void onBtnSensorClicked();
    void onBtnVersionClicked();

private:
    Ui::SelftestWin ui;
};


#endif // _SELFTEST_WIN_H_
