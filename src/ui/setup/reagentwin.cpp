#include "reagentwin.h"


ReagentWin::ReagentWin(QWidget* parent)
    : SetupFuncWin(parent)
{
    ui.setupUi(this);
}

ReagentWin::~ReagentWin()
{

}

// �ӽ����ȡ������Ϣ
void ReagentWin::getSetupInfoFromUI()
{

}

// ������Ϣ�Ƿ�仯
bool ReagentWin::isSetupInfoChanged()
{
    return true;
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString ReagentWin::isSetupInfoValid()
{
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString ReagentWin::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* ReagentWin::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// ������Ϣ��Ч��������������Ϣ��
bool ReagentWin::onSetupInfoValid()
{
    return true;
}