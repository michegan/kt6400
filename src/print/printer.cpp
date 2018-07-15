#include <QFile>
#include <QMutex>
#include <QTimer>
#include <QtDebug>
#include <QStringList>
#ifdef _WIN32
#define B57600 4097
#else
#include <termios.h>
#endif

#include "printer.h"
#include "utility.h"
#include "thermalprinter.h"


class PrinterPrivate
{
public:
    PrinterPrivate();
    ~PrinterPrivate();

    // 打印机
    AbstractPrinter* printer(const QString& cmd);

    // 设置参数
    void setPara(const QString& key, float para);
    void setPara(const QString& key, const QString& para);

    // 添加打印任务
    bool addTask(const QHash<QString, QString>& printTask);

    // 打印任务
    QString printTask(const QHash<QString, QString>& printTask);

public:
    // 定时器
    QTimer* timer;

    // 当前打印机
    QString scmd;
    QString sdevice;
    QString sprinter;

    QStringList sprinters;

    // 打印参数
    QHash<QString, QString> paras;

    // 打印机
    ThermalPrinter* thermalPrinter;
    QList<AbstractPrinter*> printers;

    // 打印任务
    QMutex* mutex;
    QList<QHash<QString, QString> > printTasks;
};

PrinterPrivate::PrinterPrivate()
    : timer(new QTimer()), scmd(""), sdevice(""), sprinter(""), 
      thermalPrinter(new ThermalPrinter("/dev/ttySAC4", B57600, 8)), mutex(new QMutex())
{
    // 低端打印机
    // this->printers.append(new LowPrinter());
    // 高端打印机
    // this->printers.append(new HighPrinter());
    // HP低端打印机
    // this->printers.append(new DeskjetPrinter());
    // 热敏打印机
    this->printers.append(this->thermalPrinter);

    // 打印机初始化
    foreach (AbstractPrinter* printer, this->printers)
    {
        printer->init();
    }

    // 每5秒检测一次打印机连接状态
    this->timer->setInterval(5 * 1000);
}

PrinterPrivate::~PrinterPrivate()
{
    // 定时器
    delete this->timer;

    // 打印任务
    delete this->mutex;

    // 打印机
    foreach (AbstractPrinter* printer, this->printers)
    {
        delete printer;
    }
}

// 打印机
AbstractPrinter* PrinterPrivate::printer(const QString& cmd)
{
    foreach (AbstractPrinter* printer, this->printers)
    {
        QStringList cmds = printer->cmds();
        if (cmds.contains(cmd))
        {
            return printer;
        }
    }
    return 0;
}

// 设置参数
void PrinterPrivate::setPara(const QString& key, float para)
{
    this->setPara(key, QString::number(para));
}

void PrinterPrivate::setPara(const QString& key, const QString& para)
{
    qDebug() << "PrinterPrivate setPara" << key << para;

    if (this->paras.contains(key))
    {
        this->paras[key] = para;
    }
    else
    {
        this->paras.insert(key, para);
    }
}

// 添加打印任务
bool PrinterPrivate::addTask(const QHash<QString, QString>& printTask)
{
    this->mutex->lock();
    this->printTasks.append(printTask);
    this->mutex->unlock();

    return true;
}

// 打印任务
QString PrinterPrivate::printTask(const QHash<QString, QString>& printTask)
{
    QString cmd = printTask.value("CMD");

    // 取对应打印机执行打印
    AbstractPrinter* printer = this->printer(cmd);
    return (printer ? printer->print(printTask) : PRINT_FAIL);
}


Printer::Printer()
    : QThread(), d(new PrinterPrivate())
{

}

Printer::~Printer()
{
    delete d;
}

// 清空参数
void Printer::clearParas()
{
    qDebug() << "Printer clearParas";

    // 清空所有参数
    d->paras.clear();
}

// 设置纸张
void Printer::setPaper(const QString& paper)
{
    d->setPara("PAPER", paper);
}

// 设置打印后是否删除文件
void Printer::setDeleteFile(bool deleteFile)
{
    d->setPara("DELETE_FILE", deleteFile ? 1 : 0);
}

// 设置打印方向
void Printer::setOrientation(QPrinter::Orientation orientation)
{
    QString sorientation = ((QPrinter::Landscape == orientation) ? "HORIZONTAL" : "VERTICAL");
    d->setPara("ORIENTATION", sorientation);
}

// 设置边距
void Printer::setFitToPage(bool fitToPage)
{
    d->setPara("FIT_TO_PAGE", fitToPage ? 1 : 0);
}

void Printer::setMargin(quint8 left, quint8 right, quint8 top, quint8 bottom)
{
    d->setPara("PAGE_LEFT", left);
    d->setPara("PAGE_RIGHT", right);
    d->setPara("PAGE_TOP", top);
    d->setPara("PAGE_BOTTOM", bottom);
}

// 外置打印（/tmp/20151027_044410_063.pdf，1）
bool Printer::usbPrint(const QString& file, int pages)
{
    QString fault;
    bool ret = false;

    qDebug() << "Printer usbPrint" << file << pages;

    do 
    {
        // 当前打印机
        QString name = d->sprinter;
        if (name.isEmpty())
        {
            qWarning() << "Printer usbPrint no printer";
            break;
        }

        // 打印命令和打印设备
        QString cmd = d->scmd;
        QString device = d->sdevice;
        qDebug() << "Printer usbPrint" << cmd << device;

        // 对应打印机
        AbstractPrinter* printer = d->printer(cmd);
        if (0 == printer)
        {
            qWarning() << "Printer usbPrint unsupport printer";
            break;
        }

        // 创建打印任务
        QHash<QString, QString> paras = d->paras;

        paras.insert("CMD", cmd);
        paras.insert("FILE", file);
        paras.insert("NAME", name);
        paras.insert("DEVICE", device);
        paras.insert("PAGES", QString::number(pages));

        // 添加打印任务
        ret = d->addTask(paras);
    } while (0);

    return ret;
}

// 热敏打印（/tmp/20151027_044410_063.bmp，1）
bool Printer::thermalPrint(const QString& file, int pages)
{
    qDebug() << "Printer thermalPrint" << file << pages;

    // 创建打印任务
    QHash<QString, QString> paras = d->paras;

    paras.insert("CMD", THERMAL_PRINTER_CMD);
    paras.insert("FILE", file);
    paras.insert("PAGES", QString::number(pages));

    // 添加打印任务
    return d->addTask(paras);
}

// 设置USB打印机监测
void Printer::setUsbPrinterMonitor(bool enable)
{
    if (enable)
    {
        d->timer->start();
    }
    else
    {
        d->timer->stop();
    }
}

// 外置打印机是否支持
bool Printer::isUsbPrinterSupported()
{
    // 对应打印机
    AbstractPrinter* printer = d->printer(d->scmd);

    // 存在对应的打印机即为支持
    return (0 != printer);
}

// 热敏打印机是否打印头过热
bool Printer::isThermalPrinterSuperHeated()
{
    // 热敏打印机
    return d->thermalPrinter->isSuperHeated();
}

// 打印机是否缺纸
bool Printer::isPrinterHasPaper(bool usbPrinter)
{
    if (usbPrinter)
    {
        // 当前外置打印机查询是否缺纸
        if (d->sprinter.isEmpty())
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        // 热敏打印机查询是否缺纸
        return d->thermalPrinter->hasPaper();
    }
}

// 打印机是否联机
bool Printer::isPrinterConnected(bool usbPrinter)
{
    if (usbPrinter)
    {
        // USB打印机
        return !d->sprinter.isEmpty();
    }
    else
    {
        // 热敏打印机
        return d->thermalPrinter->isConnected();
    }
}

// 获取热敏打印机
bool Printer::setPrinterConcentration(int conCentration)
{
    return d->thermalPrinter->setConcentration(conCentration);
}

// 线程执行体
void Printer::run()
{
    while (1)
    {
        if (d->printTasks.isEmpty())
        {
            // 等待3秒
            Utility::ssleep(3);
        }
        else
        {
            // 取打印任务
            d->mutex->lock();
            QHash<QString, QString> printTask = d->printTasks.takeFirst();
            d->mutex->unlock();

            // 打印任务
            QString ret = d->printTask(printTask);

            // 上报打印结果
            QString file = printTask.value("FILE");
            qDebug() << "Print run" << file << ret;

            // 删除打印文件
            QString remove = printTask.value("DELETE_FILE", "1");
            if ("1" == remove)
            {
                QFile::remove(file);
            }
        }
    }
}

// 当前打印机
// 默认：空
QString Printer::usbPrinter()
{
    return d->sprinter;
}

// 设置当前打印机
// 参数值为usbPrinterList返回值之一
// 默认当前打印机空，在执行打印前必须设置（设置一次）
bool Printer::setUsbPrinter(const QString& name)
{
    qDebug() << "Printer setUsbPrinter" << name;

    return false;
}

// 外置打印机列表
QStringList Printer::usbPrinterList()
{
    return d->sprinters;
}