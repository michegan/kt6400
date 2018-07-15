#ifndef _LJ_QC_FILE_WIN_
#define _LJ_QC_FILE_WIN_


#include "funcwin.h"

#include "ui_ljqcfilewin.h"

class LJQcFileTable;
class LJQcFileTableWidget;


// LJ质控文件界面
class LJQcFileWin : public FuncWin
{
    Q_OBJECT

public:
    LJQcFileWin(QWidget* parent = 0);
    virtual ~LJQcFileWin();

private slots:
    // 按钮点击
    void onBtnListClicked();
    void onBtnGraphClicked();
    void onBtnSetupClicked();

    // 行选中
    void onTableWidgetRowClicked(int row, bool selected);

private:    
    // 质控信息表
    Ui::LJQcFileWin ui;

    // 文件表
    LJQcFileTable* fileTable;

    // 文件表格
    LJQcFileTableWidget* tableWidget;
};


#endif // _LJ_QC_FILE_WIN_
