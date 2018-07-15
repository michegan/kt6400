#ifndef _PRINT_SETUP_DIALOG_H_
#define _PRINT_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_printsetupdialog.h"


// 打印设置对话框
class PrintSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    PrintSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~PrintSetupDialog();

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

private:
    // 打印设备
    QString printer;
    QStringList printers;

    // 打印报告
    QString usbReport;
    QStringList usbReports;

    QString thermalReport;
    QStringList thermalReports;

    QString printGraph;

    // 界面
    Ui::PrintSetupDialog ui;
};


#endif // _PRINT_SETUP_DIALOG_H_