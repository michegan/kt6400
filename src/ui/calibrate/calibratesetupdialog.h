#ifndef _CALIBRATE_SETUP_DIALOG_H_
#define _CALIBRATE_SETUP_DIALOG_H_


#include <QMap>

#include "para.h"
#include "setupdialog.h"
#include "ui_calibratesetupdialog.h"


// У׼���öԻ���
class CalibrateSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    CalibrateSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~CalibrateSetupDialog();

    // У׼��Ϣ�����ţ�
    QString lotNo() const;
    void setLotNo(const QString& lotNo);

    // У׼��Ϣ����ֵ��������У׼������ͨ��FLAG���֣�
    // PARA_IGNORE_FLAG����У׼�˲�����PARA_NORMAL_FLAG��У׼�˲�����
    ParaList targets() const;
    void setTargets(const ParaList& targets);

protected:
    // �����ַ���
    virtual void setWindowText();

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
    // У׼��Ϣ���޸ĺ�
    QString slotNo;
    ParaList stargets;

    // ����
    Ui::CalibrateSetupDialog ui;

    // ����ؼ�
    QMap<QString, DigitLineEdit*> valueEdits;
};


#endif // _CALIBRATE_SETUP_DIALOG_H_