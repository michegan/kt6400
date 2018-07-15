#ifndef _THERMAL_PRINTER_H_
#define _THERMAL_PRINTER_H_


#include "abstractprinter.h"


class ThermalPrinterPrivate;


// 热敏打印机命令
#define THERMAL_PRINTER_CMD     ("THERMAL")


// 热敏打印机
class ThermalPrinter : public AbstractPrinter
{
    Q_OBJECT

public:
    ThermalPrinter(const QString& name, int baudrate, int databits);
    virtual ~ThermalPrinter();

    // 初始化
    virtual bool init();

    // 是否缺纸
    virtual bool hasPaper();

    // 命令
    virtual QStringList cmds();

    // 打印
    virtual QString print(const QHash<QString, QString>& paras);

public:
    // 是否联机
    bool isConnected();

    // 是否打印机机头过热
    bool isSuperHeated();

    // 设置浓度
    bool setConcentration(int conCentration);

private:
    ThermalPrinterPrivate* d;
};


#endif // _THERMAL_PRINTER_H_