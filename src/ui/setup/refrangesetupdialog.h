#ifndef _REF_RANGE_SETUP_DIALOG_H_
#define _REF_RANGE_SETUP_DIALOG_H_


#include "para.h"
#include "setupdialog.h"
#include "ui_refrangesetupdialog.h"


// ģʽ�༭�Ի���
class RefRangeSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    RefRangeSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~RefRangeSetupDialog();

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
    void onGroupComboBoxCurrentIndexChanged(int index);
    void onSpeciesComboBoxCurrentIndexChanged(int index);

private:
    // �ؼ���
    QStringList keys1;
    QStringList keys2;

    // �ο���Χ���޸ĺ�
    ParaList lowLimits;
    ParaList highLimits;

    // ����
    Ui::RefRangeSetupDialog ui;

    // �༭��
    QMap<QString, DigitLineEdit*> lowEdits;
    QMap<QString, DigitLineEdit*> highEdits;
};


#endif // _REF_RANGE_SETUP_DIALOG_H_