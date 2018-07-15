#ifndef _PRINTER_H_
#define _PRINTER_H_


#include <QThread>
#include <QPrinter>

#include "libprint.h"


class PrinterPrivate;


// 打印
class PRINT_EXPORT Printer : public QThread
{
    Q_OBJECT

public:
    Printer();
    virtual ~Printer();

    // 清空参数
    void clearParas();

    // 设置纸张（A4，A5，LETTER）
    // 默认：A4
    void setPaper(const QString& paper);

    // 设置打印后是否删除文件（TRUE、FALSE）
    // 默认：删除
    void setDeleteFile(bool deleteFile);

    // 设置打印方向（HORIZONTAL，VERTICAL）
    // 只对高端打印机生效
    // 默认：VERTICAL
    void setOrientation(QPrinter::Orientation orientation);

    // 设置是否自适应纸张（TRUE、FALSE）
    // 设置后，setMargin设定的边距参数不再生效
    // 默认：非自适应
    void setFitToPage(bool fitToPage);

    // 设置边距（10，15，15，10）
    // 在setFitToPage为FALSE时生效
    // 默认：取决于打印机自身
    void setMargin(quint8 left, quint8 right, quint8 top, quint8 bottom);

    // 外置打印（/tmp/20151027_044410_063.pdf，1）
    bool usbPrint(const QString& file, int pages);

    // 热敏打印（/tmp/20151027_044410_063.bmp，1）
    bool thermalPrint(const QString& file, int pages);

    // 当前打印机
    // 默认：空
    QString usbPrinter();

    // 设置当前打印机
    // 参数值为usbPrinterList返回值之一
    // 默认当前打印机空，在执行打印前必须设置（设置一次）
    bool setUsbPrinter(const QString& name);

    // 外置打印机列表
    QStringList usbPrinterList();

    // 设置USB打印机监测
    void setUsbPrinterMonitor(bool enable);

    // 设置打印机浓度
    bool setPrinterConcentration(int conCentration);

public:
    // 外置打印机是否支持
    bool isUsbPrinterSupported();

    // 热敏打印机是否打印头过热
    bool isThermalPrinterSuperHeated();

    // 打印机是否缺纸
    bool isPrinterHasPaper(bool usbPrinter);

    // 打印机是否联机
    bool isPrinterConnected(bool usbPrinter);

protected:
    // 线程执行体
    virtual void run();

private:
    PrinterPrivate* d;
};


#endif // _PRINTER_H_