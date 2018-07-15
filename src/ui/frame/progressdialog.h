#ifndef _PROGRESS_DIALOG_H_
#define _PROGRESS_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_progressdialog.h"


// 手动维护对话框
class ProgressDialog : public Dialog
{
    Q_OBJECT

public:
    ProgressDialog(QWidget* parent = 0);
    virtual ~ProgressDialog();

    // 执行
    void exec(float time);

    // 用户提示
    void setText(const QString& text);

private slots:
    // 定时器超时
    void onTimerOut();

private:
    // 进度定时器
    QTimer* timer;

    // 界面
    Ui::ProgressDialog ui;
};


#endif // _PROGRESS_DIALOG_H_