#ifndef _REVIEW_SEARCH_DIALOG_H_
#define _REVIEW_SEARCH_DIALOG_H_


#include "dialog.h"
#include "ui_reviewsearchdialog.h"


// 下一样本编辑对话框
class ReviewSearchDialog : public Dialog
{
    Q_OBJECT

public:
    ReviewSearchDialog(QWidget* parent = 0);
    virtual ~ReviewSearchDialog();

    // 查询条件
    QString condition() const;

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnAllClicked();
    virtual void onBtnSearchClicked();
    virtual void onBtnCancelClicked();

private:
    // 查询条件
    QString scondition;

    // 送检者
    QStringList senders;

    // 界面
    Ui::ReviewSearchDialog ui;
};


#endif // _REVIEW_SEARCH_DIALOG_H_