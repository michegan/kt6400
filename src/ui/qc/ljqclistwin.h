#ifndef _LJ_QC_LIST_WIN_
#define _LJ_QC_LIST_WIN_


#include "funcwin.h"
#include "ui_ljqclistwin.h"

class LJQcFileTable;
class LJQcSampleTable;
class LJQcTableWidget;


// LJ质控列表界面
class LJQcListWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcListWin(QWidget* parent = 0);
    virtual ~LJQcListWin();

protected:
    // 创建状态条
    virtual void createStatusBar();

private slots:
    // 按钮点击
    void onBtnBackClicked();
    void onBtnPrintClicked();
    void onBtnDeleteClicked();

    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

    // 表格列选中
    void onColumnClicked(int columnNo, bool selected);

    // 选中样本变化
    void onSelectSampleChanged(const QList<int>& fids);

private:
    // 显示当前页
    void showCurrentPage();

private:
    // 文件号
    int fileNo;

    // 页起始
    int from;

    // 底部状态栏
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcListWin ui;

    // 全部样本
    QList<int> allSamples;

    // 文件表
    LJQcFileTable* fileTable;
    // 样本表
    LJQcSampleTable* sampleTable;

    // 样本表格
    LJQcTableWidget* tableWidget;
};


#endif // _LJ_QC_LIST_WIN_
