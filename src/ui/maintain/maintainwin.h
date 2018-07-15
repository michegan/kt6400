#ifndef _MAINTAIN_WIN_H_
#define _MAINTAIN_WIN_H_


#include "funcwin.h"

#include "ui_maintainwin.h"

class MaintainDialog;


// 主界面
class MaintainWin : public FuncWin
{
    Q_OBJECT

public:
    MaintainWin(QWidget* parent = 0);
    virtual ~MaintainWin();

private slots:
    // 按钮点击
    void onBtnFlushClicked();
    void onBtnEnhancedFlushClicked();

    void onBtnCleanClicked();
    void onBtnEnhancedCleanClicked();

    void onBtnPrimeLyseClicked();
    void onBtnPrimeDiluentClicked();

    void onBtnWholeFillClicked();
    void onBtnParkClicked();

    void onBtnInitClicked();

    void onBtnPulseClicked();

    void onBtnTscalibrateClicked();

    void onBtnHelpClicked();

private:
    // 维护按钮点击
    void onBtnMaintainClicked(const QString& text, const QString& seqNo);

private:
    Ui::MaintainWin ui;

    // 维护对话框
    MaintainDialog* dialog;
};


#endif // _MAINTAIN_WIN_H_
