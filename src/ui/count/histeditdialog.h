#ifndef _HIST_EDIT_DIALOG_H_
#define _HIST_EDIT_DIALOG_H_


#include "dialog.h"
#include "histwidget.h"
#include "ui_histeditdialog.h"


// 模式编辑对话框
class HistEditDialog : public Dialog
{
    Q_OBJECT

public:
    HistEditDialog(QWidget* parent = 0);
    virtual ~HistEditDialog();


private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 界面
    Ui::HistEditDialog ui;

    // 直方图控件
    WbcHistWidget* wbcHistWidget;
    RbcHistWidget* rbcHistWidget;
    PltHistWidget* pltHistWidget;
};


#endif // _HIST_EDIT_DIALOG_H_