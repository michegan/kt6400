#ifndef _PULSE_WIN_H_
#define _PULSE_WIN_H_


#include <QTimer>

#include "funcwin.h"
#include "pulsewidget.h"
#include "ui_pulsewin.h"


// 主界面
class PulseWin : public FuncWin
{
    Q_OBJECT

public:
    PulseWin(QWidget* parent = 0);
    virtual ~PulseWin();

protected:
    // 创建状态条
    virtual void createStatusBar();

private slots:
    // 定时器超时
    void onTimerOut();

    // 按钮点击
    void onBtnAlgClicked();

    void onBtnPageFirstClicked();
    void onBtnPageGotoClicked();
    void onBtnPageLastClicked();

    void onBtnScrollDownClicked();
    void onBtnScrollUpClicked();
    void onBtnScrollStopClicked();

    void onCheckBoxFromFileToggled(bool checked);
    void onCheckBoxFromBufferToggled(bool checked);

private:
    // 显示当前页
    void showCurrentPage();

private:
    Ui::PulseWin ui;

    // 滚动定时器
    QTimer* timer;
    int direction;

    // 显示信息
    int numOfPages;
    int currentPage;

    // 数据信息
    int wbcDataLen;
    int rbcDataLen;
    int pltDataLen;

    char* wbcDatas;
    char* rbcDatas;
    char* pltDatas;

    // 底部状态栏
    QLabel* lbPos;

    // 脉冲图形
    PulseWidget* wbcPulse;
    PulseWidget* rbcPulse;
    PulseWidget* pltPulse;
};


#endif // _PULSE_WIN_H_
