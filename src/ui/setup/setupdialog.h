#ifndef _SETUP_DIALOG_H_
#define _SETUP_DIALOG_H_


#include "dialog.h"


// 设置对话框
class SetupDialog : public Dialog
{
    Q_OBJECT

public:
    SetupDialog(QWidget* parent = 0);
    virtual ~SetupDialog();

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI() = 0;

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid() = 0;

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret) = 0;
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret) = 0;

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid() = 0;

protected slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();
};


#endif // _SETUP_DIALOG_H_