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


// 主界面
class CountWin : public CountFuncWin
{
    Q_OBJECT

public:
    CountWin(QWidget* parent = 0);
    virtual ~CountWin();

    // 吸样键按下
    virtual void onAbsorbKeyDown();

protected:
    // 界面字符串
    virtual void setWindowText();

    // 创建状态条
    virtual void createStatusBar();

    // 界面使能
    virtual void enableWindow(bool enable);

    // 显示下一样本信息
    virtual void showNextSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // 按钮点击
    void onBtnPrintClicked();
    void onBtnUnclogClicked();
    void onBtnAddDiluentClicked();
    void onBtnNextSampleClicked();

    void onBtnFirstClicked();
    void onBtnLastClicked();
    void onBtnNextClicked();
    void onBtnPreviousClicked();

    // 算法结束
    void onCountAlgFinished();
    // 计数结束
    void onCountFinished(bool result);

private:
    // 界面清空
    void clearWindow();

    // 显示当前样本
    void showCurrentSample();

    // 显示当前样本信息
    void showCurrentSampleInfo(const SampleInfo& sampleInfo);

private:
    // 计数服务
    Count* count;

    // 界面
    Ui::CountWin ui;

    // 底部状态栏
    QLabel* lbNextSample;
    QLabel* lbNextSampleId;

    // 参数结果控件
    ParaWidget* wbcParaWidget;
    ParaWidget* rbcParaWidget;
    ParaWidget* pltParaWidget;

    // 直方图控件
    WbcHistWidget* wbcHistWidget;
    RbcHistWidget* rbcHistWidget;
    PltHistWidget* pltHistWidget;

    // 进度对话框
    ProgressDialog* progressDialog;

    // 加稀释液窗口
    AddDiluentDialog* addDiluentDialog;

    // 样本数据表
    ReviewSampleTable* sampleTable;

    // 计数信息
    SampleInfo* countSampleInfo;
};


#endif // _COUNT_WIN_H_
