#ifndef _DATE_TIME_SETUP_DIALOG_H_
#define _DATE_TIME_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_datetimesetupdialog.h"


// 模式编辑对话框
class DateTimeSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    DateTimeSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DateTimeSetupDialog();

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

protected slots:
    // 按钮点击
    virtual void onBtnCancelClicked();

private slots:
    // 下拉选项变化
    void onComboBoxCurrentIndexChanged(const QString& text);

private:
    // 日期格式（更改前）
    QString dateFormat1;
    // 日期格式（更改后）
    QString dateFormat2;

    // 界面
    Ui::DateTimeSetupDialog ui;
};


#endif // _DATE_TIME_SETUP_DIALOG_H_