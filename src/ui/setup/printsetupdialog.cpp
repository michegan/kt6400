#include <QtDebug>

#include "path.h"
#include "project.h"
#include "utility.h"
#include "printxml.h"
#include "messagebox.h"
#include "printsetupdialog.h"


PrintSetupDialog::PrintSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // ��ӡ����
    PrintXml xml;
    if (xml.load())
    {
        this->printer = xml.getTextValue2(KEY1_PRINT, KEY2_PRINTER);
        this->usbReport = xml.getTextValue2(KEY1_PRINT, KEY2_USB_REPORT);
        this->thermalReport = xml.getTextValue2(KEY1_PRINT, KEY2_THERMAL_REPORT);
        this->printGraph = xml.getTextValue2(KEY1_PRINT, KEY2_PRINT_GRAPH);
    }

    // �����ַ�������Ҫλ�����������
    this->setWindowText();

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

PrintSetupDialog::~PrintSetupDialog()
{

}

// �����ַ���
void PrintSetupDialog::setWindowText()
{
    // ���ദ��
    SetupDialog::setWindowText();

    // ���ദ��
    this->printers << "IDS_USB_PRINTER" << "IDS_THERMAL_PRINTER";
    this->setItems(ui.cbPrinter, this->printer, printers);

    this->usbReports << "IDS_USB_VERTIVAL_REPORT";
    this->setItems(ui.cbUsbReport, this->usbReport, usbReports);

    this->thermalReports << "IDS_THERMAL_VERTIVAL_REPORT" << "IDS_THERMAL_HORIZONTAL_REPORT";
    this->setItems(ui.cbThermalReport, this->thermalReport, thermalReports);

    this->setText(ui.cbPrintGraph, "IDS_PRINT_GRAPH");
    ui.cbPrintGraph->setChecked("1" == this->printGraph);

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// �ӽ����ȡ������Ϣ
void PrintSetupDialog::getSetupInfoFromUI()
{

}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString PrintSetupDialog::isSetupInfoValid()
{
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString PrintSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* PrintSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// ������Ϣ��Ч��������������Ϣ��
bool PrintSetupDialog::onSetupInfoValid()
{
    bool ret = false;

    do 
    {
        PrintXml xml;
        if (!xml.load())
        {
            break;
        }

        // ������
        this->printer = this->printers.at(ui.cbPrinter->currentIndex());
        this->usbReport = this->usbReports.at(ui.cbUsbReport->currentIndex());
        this->thermalReport = this->thermalReports.at(ui.cbThermalReport->currentIndex());;
        this->printGraph = ui.cbPrintGraph->isChecked() ? "1" : "0";
        
        // ��������
        xml.setTextValue2(KEY1_PRINT, KEY2_PRINTER, this->printer);
        xml.setTextValue2(KEY1_PRINT, KEY2_USB_REPORT, this->usbReport);
        xml.setTextValue2(KEY1_PRINT, KEY2_THERMAL_REPORT, this->thermalReport);
        xml.setTextValue2(KEY1_PRINT, KEY2_PRINT_GRAPH, this->printGraph);

        // ����
        if (!xml.save())
        {
            break;
        }

        ret = true;
    } while (0);

    return ret;
}