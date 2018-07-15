#ifndef _ABSTRACT_PRINTER_H_
#define _ABSTRACT_PRINTER_H_


#include <QHash>
#include <QObject>
#include <QStringList>


// 打印结果
#define PRINT_FAIL     ("FAIL")
#define PRINT_SUCCESS  ("SUCCESS")


// 打印抽象
class AbstractPrinter : public QObject
{
    Q_OBJECT

public:
    AbstractPrinter();
    virtual ~AbstractPrinter();

    // 初始化
    virtual bool init() = 0;

    // 命令
    virtual QStringList cmds() = 0;

    // 打印
    virtual QString print(const QHash<QString, QString>& paras) = 0;
};


#endif // _ABSTRACT_PRINTER_H_