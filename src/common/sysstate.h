#ifndef _SYS_STATE_H_
#define _SYS_STATE_H_


#include <QObject>

#include "modes.h"
#include "libcommon.h"


class SysStatePrivate;


// 系统状态
class COMMON_EXPORT SysState : public QObject
{
    Q_OBJECT

public:
    // 总状态
    enum RunState
    {
        StateReady = 0x01000000, // 空闲状态
        StateRunning = 0x02000000, // 运行状态
        StateSleeping = 0x04000000, // 休眠状态
    };

    // 故障状态
    enum FaultState
    {
        StateFaultNone = 0x00010000, // 无故障状态
        StateFaultInformation = 0x00020000, // 存在故障状态（提示类故障）
        StateFaultWarning = 0x00040000, // 存在故障状态（限制类故障）
        StateFaultCritical = 0x00080000, // 存在故障状态（致命类故障）
    };

    // 开机状态
    enum StartupShutdownState
    {
        StateStaruping0 = 0x00000001, // 开机中状态（系统配置，电压自检阶段）
        StateStaruping1 = 0x00000002, // 开机中状态（温度自检，压力自检，液路初始化阶段）
        StateStaruping2 = 0x00000004, // 开机中状态（开机清洗）
        StateStaruping3 = 0x00000008, // 开机中状态（本底测量阶段）

        StateStartupFinished = 0x00000020, // 开机完成
        StateShutdowning = 0x00000040, // 关机中状态
        StateShutdownFinished = 0x00000080, // 关机完成状态
    };

public:
    SysState();
    virtual ~SysState();

    // 总状态
    quint32 state() const;

    // 运行状态
    bool isIdle() const;
    bool isSleeping() const;

    quint32 runState() const;
    void setRunState(quint32 state);

    // 故障状态
    quint32 faultState() const;
    void setFaultState(quint32 state);

    QList<int> faultList() const;

    void raiseFault(int faultId);
    void relieveFault(int faultId);

    void setFault(int fault, bool bfault);

    // 开关机状态
    bool isStartupFinished() const;
    bool isShutdownFinished() const;

    quint32 startupShutdownState() const;
    void setStartupShutdownState(quint32 state);

public:
    // 当前模式
    Modes modes() const;
    void setModes(const Modes& modes);

    // 堵孔状态
    bool bloged() const;
    void setBloged(bool bloged);

    // 吸样键使能状态
    bool isAbsorbKeyEnabled() const;
    void setAbsorbKeyState(bool enable);

    // 自动维护使能状态
    bool isAutoMaintainEnabled() const;
    void setAutoMaintainState(bool enable);

signals:
    // 吸样键状态变化
    void absorbKeyStateChanged(bool enable);

    // 自动维护状态变化
    void autoMaintainStateChanged(bool enable);

    // 故障变化
    void faultChanged(const QList<int>& faults);

    // 系统状态变化
    void runStateChanged(quint32 oldState, quint32 newState);
    void faultStateChanged(quint32 oldState, quint32 newState);
    void startupStateChanged(quint32 oldState, quint32 newState);

private:
    SysStatePrivate* d;
};


#endif // _SYS_STATE_H_