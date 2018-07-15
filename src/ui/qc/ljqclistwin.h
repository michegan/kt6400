#ifndef _LJ_QC_LIST_WIN_
#define _LJ_QC_LIST_WIN_


#include "funcwin.h"
#include "ui_ljqclistwin.h"

class LJQcFileTable;
class LJQcSampleTable;
class LJQcTableWidget;


// LJ�ʿ��б����
class LJQcListWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcListWin(QWidget* parent = 0);
    virtual ~LJQcListWin();

protected:
    // ����״̬��
    virtual void createStatusBar();

private slots:
    // ��ť���
    void onBtnBackClicked();
    void onBtnPrintClicked();
    void onBtnDeleteClicked();

    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

    // �����ѡ��
    void onColumnClicked(int columnNo, bool selected);

    // ѡ�������仯
    void onSelectSampleChanged(const QList<int>& fids);

private:
    // ��ʾ��ǰҳ
    void showCurrentPage();

private:
    // �ļ���
    int fileNo;

    // ҳ��ʼ
    int from;

    // �ײ�״̬��
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcListWin ui;

    // ȫ������
    QList<int> allSamples;

    // �ļ���
    LJQcFileTable* fileTable;
    // ������
    LJQcSampleTable* sampleTable;

    // �������
    LJQcTableWidget* tableWidget;
};


#endif // _LJ_QC_LIST_WIN_
