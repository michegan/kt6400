#ifndef _PRINTER_H_
#define _PRINTER_H_


#include <QThread>
#include <QPrinter>

#include "libprint.h"


class PrinterPrivate;


// ��ӡ
class PRINT_EXPORT Printer : public QThread
{
    Q_OBJECT

public:
    Printer();
    virtual ~Printer();

    // ��ղ���
    void clearParas();

    // ����ֽ�ţ�A4��A5��LETTER��
    // Ĭ�ϣ�A4
    void setPaper(const QString& paper);

    // ���ô�ӡ���Ƿ�ɾ���ļ���TRUE��FALSE��
    // Ĭ�ϣ�ɾ��
    void setDeleteFile(bool deleteFile);

    // ���ô�ӡ����HORIZONTAL��VERTICAL��
    // ֻ�Ը߶˴�ӡ����Ч
    // Ĭ�ϣ�VERTICAL
    void setOrientation(QPrinter::Orientation orientation);

    // �����Ƿ�����Ӧֽ�ţ�TRUE��FALSE��
    // ���ú�setMargin�趨�ı߾����������Ч
    // Ĭ�ϣ�������Ӧ
    void setFitToPage(bool fitToPage);

    // ���ñ߾ࣨ10��15��15��10��
    // ��setFitToPageΪFALSEʱ��Ч
    // Ĭ�ϣ�ȡ���ڴ�ӡ������
    void setMargin(quint8 left, quint8 right, quint8 top, quint8 bottom);

    // ���ô�ӡ��/tmp/20151027_044410_063.pdf��1��
    bool usbPrint(const QString& file, int pages);

    // ������ӡ��/tmp/20151027_044410_063.bmp��1��
    bool thermalPrint(const QString& file, int pages);

    // ��ǰ��ӡ��
    // Ĭ�ϣ���
    QString usbPrinter();

    // ���õ�ǰ��ӡ��
    // ����ֵΪusbPrinterList����ֵ֮һ
    // Ĭ�ϵ�ǰ��ӡ���գ���ִ�д�ӡǰ�������ã�����һ�Σ�
    bool setUsbPrinter(const QString& name);

    // ���ô�ӡ���б�
    QStringList usbPrinterList();

    // ����USB��ӡ�����
    void setUsbPrinterMonitor(bool enable);

    // ���ô�ӡ��Ũ��
    bool setPrinterConcentration(int conCentration);

public:
    // ���ô�ӡ���Ƿ�֧��
    bool isUsbPrinterSupported();

    // ������ӡ���Ƿ��ӡͷ����
    bool isThermalPrinterSuperHeated();

    // ��ӡ���Ƿ�ȱֽ
    bool isPrinterHasPaper(bool usbPrinter);

    // ��ӡ���Ƿ�����
    bool isPrinterConnected(bool usbPrinter);

protected:
    // �߳�ִ����
    virtual void run();

private:
    PrinterPrivate* d;
};


#endif // _PRINTER_H_