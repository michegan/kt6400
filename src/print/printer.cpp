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

    // ��ӡ��
    AbstractPrinter* printer(const QString& cmd);

    // ���ò���
    void setPara(const QString& key, float para);
    void setPara(const QString& key, const QString& para);

    // ��Ӵ�ӡ����
    bool addTask(const QHash<QString, QString>& printTask);

    // ��ӡ����
    QString printTask(const QHash<QString, QString>& printTask);

public:
    // ��ʱ��
    QTimer* timer;

    // ��ǰ��ӡ��
    QString scmd;
    QString sdevice;
    QString sprinter;

    QStringList sprinters;

    // ��ӡ����
    QHash<QString, QString> paras;

    // ��ӡ��
    ThermalPrinter* thermalPrinter;
    QList<AbstractPrinter*> printers;

    // ��ӡ����
    QMutex* mutex;
    QList<QHash<QString, QString> > printTasks;
};

PrinterPrivate::PrinterPrivate()
    : timer(new QTimer()), scmd(""), sdevice(""), sprinter(""), 
      thermalPrinter(new ThermalPrinter("/dev/ttySAC4", B57600, 8)), mutex(new QMutex())
{
    // �Ͷ˴�ӡ��
    // this->printers.append(new LowPrinter());
    // �߶˴�ӡ��
    // this->printers.append(new HighPrinter());
    // HP�Ͷ˴�ӡ��
    // this->printers.append(new DeskjetPrinter());
    // ������ӡ��
    this->printers.append(this->thermalPrinter);

    // ��ӡ����ʼ��
    foreach (AbstractPrinter* printer, this->printers)
    {
        printer->init();
    }

    // ÿ5����һ�δ�ӡ������״̬
    this->timer->setInterval(5 * 1000);
}

PrinterPrivate::~PrinterPrivate()
{
    // ��ʱ��
    delete this->timer;

    // ��ӡ����
    delete this->mutex;

    // ��ӡ��
    foreach (AbstractPrinter* printer, this->printers)
    {
        delete printer;
    }
}

// ��ӡ��
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

// ���ò���
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

// ��Ӵ�ӡ����
bool PrinterPrivate::addTask(const QHash<QString, QString>& printTask)
{
    this->mutex->lock();
    this->printTasks.append(printTask);
    this->mutex->unlock();

    return true;
}

// ��ӡ����
QString PrinterPrivate::printTask(const QHash<QString, QString>& printTask)
{
    QString cmd = printTask.value("CMD");

    // ȡ��Ӧ��ӡ��ִ�д�ӡ
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

// ��ղ���
void Printer::clearParas()
{
    qDebug() << "Printer clearParas";

    // ������в���
    d->paras.clear();
}

// ����ֽ��
void Printer::setPaper(const QString& paper)
{
    d->setPara("PAPER", paper);
}

// ���ô�ӡ���Ƿ�ɾ���ļ�
void Printer::setDeleteFile(bool deleteFile)
{
    d->setPara("DELETE_FILE", deleteFile ? 1 : 0);
}

// ���ô�ӡ����
void Printer::setOrientation(QPrinter::Orientation orientation)
{
    QString sorientation = ((QPrinter::Landscape == orientation) ? "HORIZONTAL" : "VERTICAL");
    d->setPara("ORIENTATION", sorientation);
}

// ���ñ߾�
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

// ���ô�ӡ��/tmp/20151027_044410_063.pdf��1��
bool Printer::usbPrint(const QString& file, int pages)
{
    QString fault;
    bool ret = false;

    qDebug() << "Printer usbPrint" << file << pages;

    do 
    {
        // ��ǰ��ӡ��
        QString name = d->sprinter;
        if (name.isEmpty())
        {
            qWarning() << "Printer usbPrint no printer";
            break;
        }

        // ��ӡ����ʹ�ӡ�豸
        QString cmd = d->scmd;
        QString device = d->sdevice;
        qDebug() << "Printer usbPrint" << cmd << device;

        // ��Ӧ��ӡ��
        AbstractPrinter* printer = d->printer(cmd);
        if (0 == printer)
        {
            qWarning() << "Printer usbPrint unsupport printer";
            break;
        }

        // ������ӡ����
        QHash<QString, QString> paras = d->paras;

        paras.insert("CMD", cmd);
        paras.insert("FILE", file);
        paras.insert("NAME", name);
        paras.insert("DEVICE", device);
        paras.insert("PAGES", QString::number(pages));

        // ��Ӵ�ӡ����
        ret = d->addTask(paras);
    } while (0);

    return ret;
}

// ������ӡ��/tmp/20151027_044410_063.bmp��1��
bool Printer::thermalPrint(const QString& file, int pages)
{
    qDebug() << "Printer thermalPrint" << file << pages;

    // ������ӡ����
    QHash<QString, QString> paras = d->paras;

    paras.insert("CMD", THERMAL_PRINTER_CMD);
    paras.insert("FILE", file);
    paras.insert("PAGES", QString::number(pages));

    // ��Ӵ�ӡ����
    return d->addTask(paras);
}

// ����USB��ӡ�����
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

// ���ô�ӡ���Ƿ�֧��
bool Printer::isUsbPrinterSupported()
{
    // ��Ӧ��ӡ��
    AbstractPrinter* printer = d->printer(d->scmd);

    // ���ڶ�Ӧ�Ĵ�ӡ����Ϊ֧��
    return (0 != printer);
}

// ������ӡ���Ƿ��ӡͷ����
bool Printer::isThermalPrinterSuperHeated()
{
    // ������ӡ��
    return d->thermalPrinter->isSuperHeated();
}

// ��ӡ���Ƿ�ȱֽ
bool Printer::isPrinterHasPaper(bool usbPrinter)
{
    if (usbPrinter)
    {
        // ��ǰ���ô�ӡ����ѯ�Ƿ�ȱֽ
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
        // ������ӡ����ѯ�Ƿ�ȱֽ
        return d->thermalPrinter->hasPaper();
    }
}

// ��ӡ���Ƿ�����
bool Printer::isPrinterConnected(bool usbPrinter)
{
    if (usbPrinter)
    {
        // USB��ӡ��
        return !d->sprinter.isEmpty();
    }
    else
    {
        // ������ӡ��
        return d->thermalPrinter->isConnected();
    }
}

// ��ȡ������ӡ��
bool Printer::setPrinterConcentration(int conCentration)
{
    return d->thermalPrinter->setConcentration(conCentration);
}

// �߳�ִ����
void Printer::run()
{
    while (1)
    {
        if (d->printTasks.isEmpty())
        {
            // �ȴ�3��
            Utility::ssleep(3);
        }
        else
        {
            // ȡ��ӡ����
            d->mutex->lock();
            QHash<QString, QString> printTask = d->printTasks.takeFirst();
            d->mutex->unlock();

            // ��ӡ����
            QString ret = d->printTask(printTask);

            // �ϱ���ӡ���
            QString file = printTask.value("FILE");
            qDebug() << "Print run" << file << ret;

            // ɾ����ӡ�ļ�
            QString remove = printTask.value("DELETE_FILE", "1");
            if ("1" == remove)
            {
                QFile::remove(file);
            }
        }
    }
}

// ��ǰ��ӡ��
// Ĭ�ϣ���
QString Printer::usbPrinter()
{
    return d->sprinter;
}

// ���õ�ǰ��ӡ��
// ����ֵΪusbPrinterList����ֵ֮һ
// Ĭ�ϵ�ǰ��ӡ���գ���ִ�д�ӡǰ�������ã�����һ�Σ�
bool Printer::setUsbPrinter(const QString& name)
{
    qDebug() << "Printer setUsbPrinter" << name;

    return false;
}

// ���ô�ӡ���б�
QStringList Printer::usbPrinterList()
{
    return d->sprinters;
}