#ifndef _TIMESEQ_H_
#define _TIMESEQ_H_


#include <QTimer>
#include <QObject>

#include "libtimeseq.h"

class McuComm;


// 时序执行
class TIMESEQ_EXPORT Timeseq : public QObject
{
    Q_OBJECT

public:
    Timeseq();
    virtual ~Timeseq();

    // 执行名称为seqNo的时序，可以是基本时序，也可以是功能时序
    bool runTimeseq(const QString& seqNo);

signals:
    // 数据采集结束
    void dmaDataReady();

    // 时序执行结束
    void timeseqFinished(const QString& seqNo, bool result);

private slots:
    // 定时器超时
    void onTimerOut();

    // 故障上报
    void onNewFault(int fault);

public:
    // 初始化
    static void init();

    // 稀释液传感器
    static bool hasDiluent();

    // 溶血剂传感器
    static bool hasLyse();

    // 废液传感器
    static bool isWasteFull();

    // 蜂鸣器开关
    static bool buzzer(bool open);

    // 电机初始化
    static bool motorHInit();
    static bool motorVInit();
    static bool motorSpInit();
    static bool motorVpInit();

    // 阀开关
    static bool valve(quint8 vno, bool open);

private:
    // 时序号
    QString seqNo;

    // 定时器
    QTimer* timer;

    // MCU通信
    McuComm* mcuComm;
};


#endif // _TIMESEQ_H_
