#ifndef _MACHINE_SETUP_DIALOG_H_
#define _MACHINE_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_machinesetupdialog.h"


// �������öԻ���
class MachineSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    MachineSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~MachineSetupDialog();

protected:
    // �ӽ����ȡ������Ϣ
    virtual void getSetupInfoFromUI();

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    virtual QString isSetupInfoValid();

    // ������Ϣ��Ч������ʾ��Ϣ��
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // ������Ϣ��Ч��������������Ϣ��
    virtual bool onSetupInfoValid();

private:
    // ���кţ�����ǰ��
    QString sn1;
    // ���кţ����ĺ�
    QString sn2;

    // ����棨����ǰ��
    int forPets1;
    // ����棨���ĺ�
    int forPets2;

    // ���ͣ�����ǰ��
    QString machine1;
    // ���ͣ����ĺ�
    QString machine2;

    // ���ԣ�����ǰ��
    QString language1;
    // ���ԣ����ĺ�
    QString language2;

    // �����ٶȣ�����ǰ��
    QString testSpeed1;
    // �����ٶȣ����ĺ�
    QString testSpeed2;

    // ϡ�ͱȣ�����ǰ��
    QString diluent1;
    // ϡ�ͱȣ����ĺ�
    QString diluent2;

    // ��Ѫ������������ǰ��
    QString lyse1;
    // ��Ѫ�����������ĺ�
    QString lyse2;

    // ����
    Ui::MachineSetupDialog ui;
};


#endif // _MACHINE_SETUP_DIALOG_H_