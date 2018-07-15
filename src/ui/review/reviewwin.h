#ifndef _REVIEW_WIN_H_
#define _REVIEW_WIN_H_


#include "funcwin.h"

#include "ui_reviewwin.h"

class ReviewSampleTable;
class ReviewTableWidget;


// ������
class ReviewWin : public FuncWin
{
    Q_OBJECT

public:
    ReviewWin(QWidget* parent = 0);
    virtual ~ReviewWin();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����״̬��
    virtual void createStatusBar();

private slots:
    // ��ť���
    void onBtnSearchClicked();
    void onBtnDeleteClicked();
    void onBtnPrintClicked();

    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

    void onBtnTransmitClicked();

    // �����ѡ��
    void onColumnClicked(int columnNo, bool selected);

    // ���ݱ仯
    void onDataChanged();
    // ѡ�������仯
    void onSelectSampleChanged(const QList<int>& fids);
    // ��ǰ�����仯
    void onCurrentSampleChanged(int index, const QList<int>& fids);

private:
    // ˢ��״̬��
    void updateStatusBar();

    // ��ʾ��ǰҳ
    void showCurrentPage();

private:
    Ui::ReviewWin ui;

    // ҳ��ʼ
    int from;

    // �ײ�״̬��
    QLabel* lbPos;
    QLabel* lbSelected;

    // ˽������
    ReviewSampleTable* sampleTable;

    // �б�
    ReviewTableWidget* tableWidget;
};


#endif // _REVIEW_WIN_H_
