#ifndef _COUNT_WIN_H_
#define _COUNT_WIN_H_


#include "histwidget.h"
#include "parawidget.h"
#include "ui_countwin.h"
#include "countfuncwin.h"
#include "progressdialog.h"

class Count;
class AddDiluentDialog;
class ReviewSampleTable;


// ������
class CountWin : public CountFuncWin
{
    Q_OBJECT

public:
    CountWin(QWidget* parent = 0);
    virtual ~CountWin();

    // ����������
    virtual void onAbsorbKeyDown();

protected:
    // �����ַ���
    virtual void setWindowText();

    // ����״̬��
    virtual void createStatusBar();

    // ����ʹ��
    virtual void enableWindow(bool enable);

    // ��ʾ��һ������Ϣ
    virtual void showNextSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // ��ť���
    void onBtnPrintClicked();
    void onBtnUnclogClicked();
    void onBtnAddDiluentClicked();
    void onBtnNextSampleClicked();

    void onBtnFirstClicked();
    void onBtnLastClicked();
    void onBtnNextClicked();
    void onBtnPreviousClicked();

    // �㷨����
    void onCountAlgFinished();
    // ��������
    void onCountFinished(bool result);

private:
    // �������
    void clearWindow();

    // ��ʾ��ǰ����
    void showCurrentSample();

    // ��ʾ��ǰ������Ϣ
    void showCurrentSampleInfo(const SampleInfo& sampleInfo);

private:
    // ��������
    Count* count;

    // ����
    Ui::CountWin ui;

    // �ײ�״̬��
    QLabel* lbNextSample;
    QLabel* lbNextSampleId;

    // ��������ؼ�
    ParaWidget* wbcParaWidget;
    ParaWidget* rbcParaWidget;
    ParaWidget* pltParaWidget;

    // ֱ��ͼ�ؼ�
    WbcHistWidget* wbcHistWidget;
    RbcHistWidget* rbcHistWidget;
    PltHistWidget* pltHistWidget;

    // ���ȶԻ���
    ProgressDialog* progressDialog;

    // ��ϡ��Һ����
    AddDiluentDialog* addDiluentDialog;

    // �������ݱ�
    ReviewSampleTable* sampleTable;

    // ������Ϣ
    SampleInfo* countSampleInfo;
};


#endif // _COUNT_WIN_H_
