#ifndef _SETUP_WIN_H_
#define _SETUP_WIN_H_


#include "funcwin.h"

#include "ui_setupwin.h"


// 主界面
class SetupWin : public FuncWin
{
    Q_OBJECT

public:
    SetupWin(QWidget* parent = 0);
    virtual ~SetupWin();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    void onBtnGainClicked();
    void onBtnUserClicked();
    void onBtnPrintClicked();
    void onBtnDoctorClicked();
    void onBtnMachineClicked();
    void onBtnDateTimeClicked();
    void onBtnParaUnitClicked();
    void onBtnRefRangeClicked();
    void onBtnCalFactorClicked();
    void onBtnDepartmentClicked();

private:
    Ui::SetupWin ui;
};


#endif // _SETUP_WIN_H_
