#ifndef _CAL_FACTOR_SETUP_DIALOG_H_
#define _CAL_FACTOR_SETUP_DIALOG_H_


#include <QMap>

#include "calfactor.h"
#include "setupdialog.h"
#include "ui_calfactorsetupdialog.h"


// У׼ϵ���༭�Ի���
class CalFactorSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    CalFactorSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~CalFactorSetupDialog();

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
    // ��ť���
    void onBtnPrintClicked();

private:
    // �ؼ���
    QString key1() const;

private:
    // У׼ϵ�����޸ĺ�
    QMap<QString, float> peripheralValues;
    QMap<QString, float> prediluentValues;
    QMap<QString, float> wholeBloodValues;

    // ����
    Ui::CalFactorSetupDialog ui;

    // ����ؼ�
    QMap<QString, DigitLineEdit*> peripheralValueEdits;
    QMap<QString, DigitLineEdit*> prediluentValueEdits;
    QMap<QString, DigitLineEdit*> wholeBloodValueEdits;
};


#endif // _CAL_FACTOR_SETUP_DIALOG_H_