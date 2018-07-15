#ifndef _REVIEW_DELETE_DIALOG_H_
#define _REVIEW_DELETE_DIALOG_H_


#include "dialog.h"
#include "ui_reviewdeletedialog.h"


// 下一样本编辑对话框
class ReviewDeleteDialog : public Dialog
{
    Q_OBJECT

public:
    ReviewDeleteDialog(QWidget* parent = 0);
    virtual ~ReviewDeleteDialog();

    // 选项
    bool isDeleteAll() const;

protected:
    // 界面字符串
    virtual void setWindowText();

private:
    // 界面
    Ui::ReviewDeleteDialog ui;
};


#endif // _REVIEW_DELETE_DIALOG_H_