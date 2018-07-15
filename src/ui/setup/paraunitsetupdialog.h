#ifndef _PARA_UNIT_SETUP_DIALOG_H_
#define _PARA_UNIT_SETUP_DIALOG_H_


#include "unitwidget.h"
#include "setupdialog.h"
#include "ui_paraunitsetupdialog.h"


// ģʽ�༭�Ի���
class ParaUnitSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    ParaUnitSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~ParaUnitSetupDialog();

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

private slots:
    // ������ǰѡ��仯
    void onComboBoxCurrentIndexChanged (const QString& text);

private:
    // ��λ�ƣ�����ǰ��
    QString unit1;
    // ��λ�ƣ����ĺ�
    QString unit2;

    // ��λ�ؼ�
    UnitWidget* wbcUnitWidget;
    UnitWidget* rbcUnitWidget;
    UnitWidget* pltUnitWidget;

    // ����
    Ui::ParaUnitSetupDialog ui;
};


#endif // _PARA_UNIT_SETUP_DIALOG_H_