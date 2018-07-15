#ifndef _DESKJET_PRINTER_H_
#define _DESKJET_PRINTER_H_


#include "abstractprinter.h"


class DeskjetPrinterPrivate;


// HP��ī��ӡ��
class DeskjetPrinter : public AbstractPrinter
{
public:
    DeskjetPrinter();
    virtual ~DeskjetPrinter();

    // ��ʼ��
    virtual bool init();

    // ����
    virtual QStringList cmds();

    // ��ӡ
    virtual QString print(const QHash<QString, QString>& paras);

private:
    DeskjetPrinterPrivate* d;
};


#endif // _DESKJET_PRINTER_H_