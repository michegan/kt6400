#ifndef _REAGENT_WIN_H_
#define _REAGENT_WIN_H_


#include "setupfuncwin.h"
#include "ui_reagentwin.h"


// 增益设置功能窗口
class ReagentWin : public SetupFuncWin
{
    Q_OBJECT

public:
    ReagentWin(QWidget* parent = 0);
    virtual ~ReagentWin();

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI();

    // 设置信息是否变化
    virtual bool isSetupInfoChanged();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid();

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid();

private:
    // 界面
    Ui::ReagentWin ui;
};


#endif // _REAGENT_WIN_H_