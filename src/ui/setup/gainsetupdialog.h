#ifndef _GAIN_SETUP_DIALOG_H_
#define _GAIN_SETUP_DIALOG_H_


#include <QTimer>

#include "setupdialog.h"
#include "ui_gainsetupdialog.h"


// �������öԻ���
class GainSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    GainSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~GainSetupDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

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
    // ��ʱ����ʱ
    void onTimerOut();

private:
    // ��ʱ��
    QTimer* timer;

    // ����
    Ui::GainSetupDialog ui;

    // ��������
    QMap<QString, int> cmds;

    // ����ֵ
    QMap<QString, QString> gains;
};


#endif // _GAIN_SETUP_DIALOG_H_