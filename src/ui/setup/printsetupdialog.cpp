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

    // 打印设置
    PrintXml xml;
    if (xml.load())
    {
        this->printer = xml.getTextValue2(KEY1_PRINT, KEY2_PRINTER);
        this->usbReport = xml.getTextValue2(KEY1_PRINT, KEY2_USB_REPORT);
        this->thermalReport = xml.getTextValue2(KEY1_PRINT, KEY2_THERMAL_REPORT);
        this->printGraph = xml.getTextValue2(KEY1_PRINT, KEY2_PRINT_GRAPH);
    }

    // 界面字符串（需要位于上述代码后）
    this->setWindowText();

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

PrintSetupDialog::~PrintSetupDialog()
{

}

// 界面字符串
void PrintSetupDialog::setWindowText()
{
    // 基类处理
    SetupDialog::setWindowText();

    // 子类处理
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

// 从界面获取设置信息
void PrintSetupDialog::getSetupInfoFromUI()
{

}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString PrintSetupDialog::isSetupInfoValid()
{
    return QString();
}

// 设置信息无效处理（提示信息）
QString PrintSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* PrintSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// 设置信息有效处理（保存设置信息）
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

        // 新设置
        this->printer = this->printers.at(ui.cbPrinter->currentIndex());
        this->usbReport = this->usbReports.at(ui.cbUsbReport->currentIndex());
        this->thermalReport = this->thermalReports.at(ui.cbThermalReport->currentIndex());;
        this->printGraph = ui.cbPrintGraph->isChecked() ? "1" : "0";
        
        // 更新配置
        xml.setTextValue2(KEY1_PRINT, KEY2_PRINTER, this->printer);
        xml.setTextValue2(KEY1_PRINT, KEY2_USB_REPORT, this->usbReport);
        xml.setTextValue2(KEY1_PRINT, KEY2_THERMAL_REPORT, this->thermalReport);
        xml.setTextValue2(KEY1_PRINT, KEY2_PRINT_GRAPH, this->printGraph);

        // 保存
        if (!xml.save())
        {
            break;
        }

        ret = true;
    } while (0);

    return ret;
}