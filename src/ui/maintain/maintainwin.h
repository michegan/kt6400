#ifndef _MAINTAIN_WIN_H_
#define _MAINTAIN_WIN_H_


#include "funcwin.h"

#include "ui_maintainwin.h"

class MaintainDialog;


// ������
class MaintainWin : public FuncWin
{
    Q_OBJECT

public:
    MaintainWin(QWidget* parent = 0);
    virtual ~MaintainWin();

private slots:
    // ��ť���
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
    // ά����ť���
    void onBtnMaintainClicked(const QString& text, const QString& seqNo);

private:
    Ui::MaintainWin ui;

    // ά���Ի���
    MaintainDialog* dialog;
};


#endif // _MAINTAIN_WIN_H_
