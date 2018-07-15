#ifndef _THERMAL_PRINTER_H_
#define _THERMAL_PRINTER_H_


#include "abstractprinter.h"


class ThermalPrinterPrivate;


// ������ӡ������
#define THERMAL_PRINTER_CMD     ("THERMAL")


// ������ӡ��
class ThermalPrinter : public AbstractPrinter
{
    Q_OBJECT

public:
    ThermalPrinter(const QString& name, int baudrate, int databits);
    virtual ~ThermalPrinter();

    // ��ʼ��
    virtual bool init();

    // �Ƿ�ȱֽ
    virtual bool hasPaper();

    // ����
    virtual QStringList cmds();

    // ��ӡ
    virtual QString print(const QHash<QString, QString>& paras);

public:
    // �Ƿ�����
    bool isConnected();

    // �Ƿ��ӡ����ͷ����
    bool isSuperHeated();

    // ����Ũ��
    bool setConcentration(int conCentration);

private:
    ThermalPrinterPrivate* d;
};


#endif // _THERMAL_PRINTER_H_