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

// ��ʼ��
bool DeskjetPrinter::init()
{
    return true;
}

// ����
QStringList DeskjetPrinter::cmds()
{
    QStringList cmds;
    cmds << "DJT";
    return cmds;
}

// ��ӡ
// script/lowPrinter.sh�Բ���˳����Ҫ�󣨴�ӡ�豸������ӡ�ļ���ֽ�ͣ�ֽ�Ŵ�С��ҳ�����Ƿ�ɾ���ļ���
// ʾ����sh script/lowPrinter.sh /dev/usb/lp0 /tmp/20151027_045725_183.pdf a4 -r1200x600 1 1
QString DeskjetPrinter::print(const QHash<QString, QString>& paras)
{
    QString ret = PRINT_FAIL;
    QString cmd = "sh script/deskjetPrinter.sh";

    do 
    {
        // ����ӡ���Ƿ�ȱֽ
        QString device = paras.value("DEVICE");
        if (false) // !HalPrinter::hasPaper(device))
        {
            ret = "ERR_PRINTER_OUT_OF_PAPER";
            break;
        }

        // �ļ�
        QString file = paras.value("FILE");
        qDebug() << "DeskjetPrinter print" << file;

        if (!QFile::exists(file))
        {
            qWarning() << "DeskjetPrinter print no file";
            break;
        }

        // ����1���豸
        cmd += " " + device;

        // ����2���ļ�
        cmd += " " + file;

        // ����3��ֽ��
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

        // ����4������
        QString orientation = paras.value("ORIENTATION", "VERTICAL").toUpper();
        if ("HORIZONTAL" == orientation)
        {
            // ����
            cmd += " 4";
        } 
        else
        {
            // ����
            cmd += " 3";
        }

        // ִ�д�ӡ
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