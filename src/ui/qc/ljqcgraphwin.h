#ifndef _LJ_QC_GRAPH_WIN_H_
#define _LJ_QC_GRAPH_WIN_H_


#include "funcwin.h"
#include "ui_ljqcgraphwin.h"

class LJQcFileTable;


// 主界面
class LJQcGraphWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcGraphWin(QWidget* parent = 0);
    virtual ~LJQcGraphWin();

protected:
    // 创建状态条
    virtual void createStatusBar();

private slots:
    // 按钮点击
    void onBtnBackClicked();

private:
    // 文件号
    int fileNo;

    // 底部状态栏
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcGraphWin ui;

    // 文件表
    LJQcFileTable* fileTable;
};


#endif // _LJ_QC_GRAPH_WIN_H_
