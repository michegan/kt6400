#ifndef _DESKJET_PRINTER_H_
#define _DESKJET_PRINTER_H_


#include "abstractprinter.h"


class DeskjetPrinterPrivate;


// HP喷墨打印机
class DeskjetPrinter : public AbstractPrinter
{
public:
    DeskjetPrinter();
    virtual ~DeskjetPrinter();

    // 初始化
    virtual bool init();

    // 命令
    virtual QStringList cmds();

    // 打印
    virtual QString print(const QHash<QString, QString>& paras);

private:
    DeskjetPrinterPrivate* d;
};


#endif // _DESKJET_PRINTER_H_