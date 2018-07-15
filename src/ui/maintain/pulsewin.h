#ifndef _PULSE_WIN_H_
#define _PULSE_WIN_H_


#include <QTimer>

#include "funcwin.h"
#include "pulsewidget.h"
#include "ui_pulsewin.h"


// ������
class PulseWin : public FuncWin
{
    Q_OBJECT

public:
    PulseWin(QWidget* parent = 0);
    virtual ~PulseWin();

protected:
    // ����״̬��
    virtual void createStatusBar();

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

    // ��ť���
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
    // ��ʾ��ǰҳ
    void showCurrentPage();

private:
    Ui::PulseWin ui;

    // ������ʱ��
    QTimer* timer;
    int direction;

    // ��ʾ��Ϣ
    int numOfPages;
    int currentPage;

    // ������Ϣ
    int wbcDataLen;
    int rbcDataLen;
    int pltDataLen;

    char* wbcDatas;
    char* rbcDatas;
    char* pltDatas;

    // �ײ�״̬��
    QLabel* lbPos;

    // ����ͼ��
    PulseWidget* wbcPulse;
    PulseWidget* rbcPulse;
    PulseWidget* pltPulse;
};


#endif // _PULSE_WIN_H_
