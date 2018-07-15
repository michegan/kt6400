#ifndef _SENSOR_DIALOG_H_
#define _SENSOR_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_sensordialog.h"


// 模式编辑对话框
class SensorDialog : public Dialog
{
    Q_OBJECT

public:
    SensorDialog(QWidget* parent = 0);
    virtual ~SensorDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 定时器超时
    void onTimerOut();

private:
    // 定时器
    QTimer* timer;

    // 界面
    Ui::SensorDialog ui;
};


#endif // _SENSOR_DIALOG_H_