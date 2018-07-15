#ifndef _SETUP_DIALOG_H_
#define _SETUP_DIALOG_H_


#include "dialog.h"


// ���öԻ���
class SetupDialog : public Dialog
{
    Q_OBJECT

public:
    SetupDialog(QWidget* parent = 0);
    virtual ~SetupDialog();

protected:
    // �ӽ����ȡ������Ϣ
    virtual void getSetupInfoFromUI() = 0;

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    virtual QString isSetupInfoValid() = 0;

    // ������Ϣ��Ч������ʾ��Ϣ��
    virtual QString onSetupInfoInvalidText(const QString& ret) = 0;
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret) = 0;

    // ������Ϣ��Ч��������������Ϣ��
    virtual bool onSetupInfoValid() = 0;

protected slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();
};


#endif // _SETUP_DIALOG_H_