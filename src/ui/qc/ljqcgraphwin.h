#ifndef _LJ_QC_GRAPH_WIN_H_
#define _LJ_QC_GRAPH_WIN_H_


#include "funcwin.h"
#include "ui_ljqcgraphwin.h"

class LJQcFileTable;


// ������
class LJQcGraphWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcGraphWin(QWidget* parent = 0);
    virtual ~LJQcGraphWin();

protected:
    // ����״̬��
    virtual void createStatusBar();

private slots:
    // ��ť���
    void onBtnBackClicked();

private:
    // �ļ���
    int fileNo;

    // �ײ�״̬��
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcGraphWin ui;

    // �ļ���
    LJQcFileTable* fileTable;
};


#endif // _LJ_QC_GRAPH_WIN_H_
