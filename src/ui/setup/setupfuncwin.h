#ifndef _SETUP_FUNC_WIN_H_
#define _SETUP_FUNC_WIN_H_


#include "funcwin.h"


// 设置信息有效
#define SETUP_INFO_VALID                ("")


// 设置功能窗口
class SetupFuncWin : public FuncWin
{
    Q_OBJECT

public:
    SetupFuncWin(QWidget* parent = 0);
    virtual ~SetupFuncWin();

protected:
    // 切换到功能窗口
    virtual void switchToFuncWin(FuncWin* funcWin);

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI() = 0;

    // 设置信息是否变化
    virtual bool isSetupInfoChanged() = 0;

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid() = 0;

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret) = 0;
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret) = 0;

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid() = 0;
};


#endif // _SETUP_FUNC_WIN_H_