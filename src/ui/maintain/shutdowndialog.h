#ifndef _SHUTDOWN_DIALOG_H_
#define _SHUTDOWN_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_shutdowndialog.h"


// 模式编辑对话框
class ShutDownDialog : public Dialog
{
    Q_OBJECT

public:
    ShutDownDialog(QWidget* parent = 0);
    virtual ~ShutDownDialog();

private slots:
    // 定时器超时
    void onTimerOut();

private:
    // 关机进度
    int steps;

    // 定时器
    QTimer* timer;

    // 界面
    Ui::ShutDownDialog ui;
};


#endif // _SHUTDOWN_DIALOG_H_