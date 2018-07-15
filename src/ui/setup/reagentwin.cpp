#include "reagentwin.h"


ReagentWin::ReagentWin(QWidget* parent)
    : SetupFuncWin(parent)
{
    ui.setupUi(this);
}

ReagentWin::~ReagentWin()
{

}

// 从界面获取设置信息
void ReagentWin::getSetupInfoFromUI()
{

}

// 设置信息是否变化
bool ReagentWin::isSetupInfoChanged()
{
    return true;
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString ReagentWin::isSetupInfoValid()
{
    return QString();
}

// 设置信息无效处理（提示信息）
QString ReagentWin::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* ReagentWin::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// 设置信息有效处理（保存设置信息）
bool ReagentWin::onSetupInfoValid()
{
    return true;
}