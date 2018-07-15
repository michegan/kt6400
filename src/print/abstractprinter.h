#ifndef _ABSTRACT_PRINTER_H_
#define _ABSTRACT_PRINTER_H_


#include <QHash>
#include <QObject>
#include <QStringList>


// ��ӡ���
#define PRINT_FAIL     ("FAIL")
#define PRINT_SUCCESS  ("SUCCESS")


// ��ӡ����
class AbstractPrinter : public QObject
{
    Q_OBJECT

public:
    AbstractPrinter();
    virtual ~AbstractPrinter();

    // ��ʼ��
    virtual bool init() = 0;

    // ����
    virtual QStringList cmds() = 0;

    // ��ӡ
    virtual QString print(const QHash<QString, QString>& paras) = 0;
};


#endif // _ABSTRACT_PRINTER_H_