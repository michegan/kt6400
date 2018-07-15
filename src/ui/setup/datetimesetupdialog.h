#ifndef _DATE_TIME_SETUP_DIALOG_H_
#define _DATE_TIME_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_datetimesetupdialog.h"


// ģʽ�༭�Ի���
class DateTimeSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    DateTimeSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DateTimeSetupDialog();

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

protected slots:
    // ��ť���
    virtual void onBtnCancelClicked();

private slots:
    // ����ѡ��仯
    void onComboBoxCurrentIndexChanged(const QString& text);

private:
    // ���ڸ�ʽ������ǰ��
    QString dateFormat1;
    // ���ڸ�ʽ�����ĺ�
    QString dateFormat2;

    // ����
    Ui::DateTimeSetupDialog ui;
};


#endif // _DATE_TIME_SETUP_DIALOG_H_