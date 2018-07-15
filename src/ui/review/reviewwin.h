#ifndef _REVIEW_WIN_H_
#define _REVIEW_WIN_H_


#include "funcwin.h"

#include "ui_reviewwin.h"

class ReviewSampleTable;
class ReviewTableWidget;


// 主界面
class ReviewWin : public FuncWin
{
    Q_OBJECT

public:
    ReviewWin(QWidget* parent = 0);
    virtual ~ReviewWin();

protected:
    // 界面字符串
    virtual void setWindowText();

    // 创建状态条
    virtual void createStatusBar();

private slots:
    // 按钮点击
    void onBtnSearchClicked();
    void onBtnDeleteClicked();
    void onBtnPrintClicked();

    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

    void onBtnTransmitClicked();

    // 表格列选中
    void onColumnClicked(int columnNo, bool selected);

    // 数据变化
    void onDataChanged();
    // 选中样本变化
    void onSelectSampleChanged(const QList<int>& fids);
    // 当前样本变化
    void onCurrentSampleChanged(int index, const QList<int>& fids);

private:
    // 刷新状态栏
    void updateStatusBar();

    // 显示当前页
    void showCurrentPage();

private:
    Ui::ReviewWin ui;

    // 页起始
    int from;

    // 底部状态栏
    QLabel* lbPos;
    QLabel* lbSelected;

    // 私有数据
    ReviewSampleTable* sampleTable;

    // 列表
    ReviewTableWidget* tableWidget;
};


#endif // _REVIEW_WIN_H_
