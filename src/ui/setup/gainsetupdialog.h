#ifndef _GAIN_SETUP_DIALOG_H_
#define _GAIN_SETUP_DIALOG_H_


#include <QTimer>

#include "setupdialog.h"
#include "ui_gainsetupdialog.h"


// 增益设置对话框
class GainSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    GainSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~GainSetupDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid();

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid();

private slots:
    // 定时器超时
    void onTimerOut();

private:
    // 定时器
    QTimer* timer;

    // 界面
    Ui::GainSetupDialog ui;

    // 设置命令
    QMap<QString, int> cmds;

    // 增益值
    QMap<QString, QString> gains;
};


#endif // _GAIN_SETUP_DIALOG_H_