#ifndef _SETUP_FUNC_WIN_H_
#define _SETUP_FUNC_WIN_H_


#include "funcwin.h"


// ������Ϣ��Ч
#define SETUP_INFO_VALID                ("")


// ���ù��ܴ���
class SetupFuncWin : public FuncWin
{
    Q_OBJECT

public:
    SetupFuncWin(QWidget* parent = 0);
    virtual ~SetupFuncWin();

protected:
    // �л������ܴ���
    virtual void switchToFuncWin(FuncWin* funcWin);

protected:
    // �ӽ����ȡ������Ϣ
    virtual void getSetupInfoFromUI() = 0;

    // ������Ϣ�Ƿ�仯
    virtual bool isSetupInfoChanged() = 0;

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    virtual QString isSetupInfoValid() = 0;

    // ������Ϣ��Ч������ʾ��Ϣ��
    virtual QString onSetupInfoInvalidText(const QString& ret) = 0;
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret) = 0;

    // ������Ϣ��Ч��������������Ϣ��
    virtual bool onSetupInfoValid() = 0;
};


#endif // _SETUP_FUNC_WIN_H_