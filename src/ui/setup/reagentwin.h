#ifndef _REAGENT_WIN_H_
#define _REAGENT_WIN_H_


#include "setupfuncwin.h"
#include "ui_reagentwin.h"


// �������ù��ܴ���
class ReagentWin : public SetupFuncWin
{
    Q_OBJECT

public:
    ReagentWin(QWidget* parent = 0);
    virtual ~ReagentWin();

protected:
    // �ӽ����ȡ������Ϣ
    virtual void getSetupInfoFromUI();

    // ������Ϣ�Ƿ�仯
    virtual bool isSetupInfoChanged();

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    virtual QString isSetupInfoValid();

    // ������Ϣ��Ч������ʾ��Ϣ��
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // ������Ϣ��Ч��������������Ϣ��
    virtual bool onSetupInfoValid();

private:
    // ����
    Ui::ReagentWin ui;
};


#endif // _REAGENT_WIN_H_