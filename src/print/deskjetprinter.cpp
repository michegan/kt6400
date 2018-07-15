#include <QFile>
#include <QtDebug>
#include <QProcess>

#include "enum.h"
#include "deskjetprinter.h"


class DeskjetPrinterPrivate
{
public:
    DeskjetPrinterPrivate();
    ~DeskjetPrinterPrivate();

public:

};

DeskjetPrinterPrivate::DeskjetPrinterPrivate()
{

}

DeskjetPrinterPrivate::~DeskjetPrinterPrivate()
{

}


DeskjetPrinter::DeskjetPrinter()
    : AbstractPrinter(), d(new DeskjetPrinterPrivate())
{

}

DeskjetPrinter::~DeskjetPrinter()
{
    delete d;
}

// 初始化
bool DeskjetPrinter::init()
{
    return true;
}

// 命令
QStringList DeskjetPrinter::cmds()
{
    QStringList cmds;
    cmds << "DJT";
    return cmds;
}

// 打印
// script/lowPrinter.sh对参数顺序有要求（打印设备，待打印文件，纸型，纸张大小，页数，是否删除文件）
// 示例：sh script/lowPrinter.sh /dev/usb/lp0 /tmp/20151027_045725_183.pdf a4 -r1200x600 1 1
QString DeskjetPrinter::print(const QHash<QString, QString>& paras)
{
    QString ret = PRINT_FAIL;
    QString cmd = "sh script/deskjetPrinter.sh";

    do 
    {
        // 检测打印机是否缺纸
        QString device = paras.value("DEVICE");
        if (false) // !HalPrinter::hasPaper(device))
        {
            ret = "ERR_PRINTER_OUT_OF_PAPER";
            break;
        }

        // 文件
        QString file = paras.value("FILE");
        qDebug() << "DeskjetPrinter print" << file;

        if (!QFile::exists(file))
        {
            qWarning() << "DeskjetPrinter print no file";
            break;
        }

        // 参数1：设备
        cmd += " " + device;

        // 参数2：文件
        cmd += " " + file;

        // 参数3：纸型
        QString paper = paras.value("PAPER").toUpper();
        if (paper == "A5")
        {
            cmd += " a5";
        }
        else if (paper == "A4")
        {
            cmd += " a4";
        }
        else
        {
            cmd += " " + paper.toUpper();
        }

        // 参数4：方向
        QString orientation = paras.value("ORIENTATION", "VERTICAL").toUpper();
        if ("HORIZONTAL" == orientation)
        {
            // 横向
            cmd += " 4";
        } 
        else
        {
            // 纵向
            cmd += " 3";
        }

        // 执行打印
        qDebug() << "DeskjetPrinter print" << cmd;
        if (0 != QProcess::execute(cmd))
        {
            qWarning() << "DeskjetPrinter print execute fail";
            break;
        }

        ret = PRINT_SUCCESS;
    }while(0);

    return ret;
}