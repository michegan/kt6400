#ifndef _PRINT_SETUP_DIALOG_H_
#define _PRINT_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_printsetupdialog.h"


// ��ӡ���öԻ���
class PrintSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    PrintSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~PrintSetupDialog();

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

private:
    // ��ӡ�豸
    QString printer;
    QStringList printers;

    // ��ӡ����
    QString usbReport;
    QStringList usbReports;

    QString thermalReport;
    QStringList thermalReports;

    QString printGraph;

    // ����
    Ui::PrintSetupDialog ui;
};


#endif // _PRINT_SETUP_DIALOG_H_