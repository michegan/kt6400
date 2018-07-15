#include <QtDebug>
#include <QStringList>

#include "sysstate.h"


class SysStatePrivate
{
public:
    SysStatePrivate();
    ~SysStatePrivate();

    // 总状态
    quint32 getState();

    // 子状态
    quint32 getSubState(quint32 mask);
    quint32 setSubState(quint32 state, quint32 mask);

public:
    // 总状态
    quint32 state;

    // 当前模式信息
    Modes modes;

    // 堵孔状态
    bool bloged;

    // 故障列表
    QList<int> faults;

    // 吸样键使能状态
    bool absorbKeyState;

    // 自动维护使能状态
    bool autoMaintainState;
};

SysStatePrivate::SysStatePrivate()
    : state(SysState::StateReady | SysState::StateFaultNone | SysState::StateStaruping0), 
      modes(Modes()), bloged(false), absorbKeyState(true), autoMaintainState(true)
{

}

SysStatePrivate::~SysStatePrivate()
{

}

// 总状态
quint32 SysStatePrivate::getState()
{
    return this->state;
}

quint32 SysStatePrivate::getSubState(quint32 mask)
{
    return (this->state & mask);
}

quint32 SysStatePrivate::setSubState(quint32 state, quint32 mask)
{
    // 原状态
    quint32 oldState = this->getState();

    // 新状态
    quint32 newState = ((oldState & ~mask) | (state & mask));
    qDebug() << "SysState setSubState" << QString::number(oldState, 16) << "->" << QString::number(newState, 16);

    // 更新当前状态
    this->state = newState;

    // 返回原状态
    return oldState;
}


SysState::SysState()
    : d(new SysStatePrivate())
{

}

SysState::~SysState()
{
    delete d;
}

// 总状态
quint32 SysState::state() const
{
    return d->state;
}

// 运行状态
bool SysState::isIdle() const
{
    return (SysState::StateReady == this->runState());
}

bool SysState::isSleeping() const
{
    return (SysState::StateSleeping == this->runState());
}

quint32 SysState::runState() const
{
    return d->getSubState(0xFF00000);
}

void SysState::setRunState(quint32 state)
{
    quint32 newState = state;
    quint32 oldState = this->runState();

    // 状态变化
    if (oldState != newState)
    {
        // 更新子状态
        d->setSubState(newState, 0xFF00000);

        // 状态变化信号
        emit runStateChanged(oldState, newState);
    }
}

// 故障状态
quint32 SysState::faultState() const
{
    return d->getSubState(0x00FF0000);
}

void SysState::setFaultState(quint32 state)
{
    quint32 newState = state;
    quint32 oldState = this->faultState();

    // 状态变化
    if (oldState != newState)
    {
        // 更新子状态
        d->setSubState(newState, 0x00FF0000);

        // 状态变化信号
        emit faultStateChanged(oldState, newState);
    }
}

QList<int> SysState::faultList() const
{
    return d->faults;
}

void SysState::raiseFault(int faultId)
{
    if (!d->faults.contains(faultId))
    {
        d->faults.append(faultId);

        // 故障变化信号
        emit faultChanged(d->faults);

        // 故障状态变化
        this->setFaultState(SysState::StateFaultWarning);
    }
}

void SysState::relieveFault(int faultId)
{
    if (d->faults.contains(faultId))
    {
        d->faults.removeOne(faultId);

        // 故障变化信号
        emit faultChanged(d->faults);

        // 故障状态变化
        if (d->faults.isEmpty())
        {
            this->setFaultState(SysState::StateFaultNone);
        }
    }
}

void SysState::setFault(int fault, bool bfault)
{
    if (bfault)
    {
        this->raiseFault(fault);
    }
    else
    {
        this->relieveFault(fault);
    }
}

// 开关机状态
bool SysState::isStartupFinished() const
{
    return (SysState::StateStartupFinished == this->startupShutdownState());
}

bool SysState::isShutdownFinished() const
{
    return (SysState::StateShutdownFinished == this->startupShutdownState());
}

quint32 SysState::startupShutdownState() const
{
    return d->getSubState(0x000000FF);
}

void SysState::setStartupShutdownState(quint32 state)
{
    quint32 newState = state;
    quint32 oldState = this->startupShutdownState();

    // 状态变化
    if (oldState != newState)
    {
        // 更新子状态
        d->setSubState(newState, 0x000000FF);
    
        // 状态变化信号
        emit startupStateChanged(oldState, newState);
    }
}

// 当前模式
Modes SysState::modes() const
{
    return d->modes;
}

void SysState::setModes(const Modes& modes)
{
    d->modes = modes;
}

// 堵孔状态
bool SysState::bloged() const
{
    return d->bloged;
}

void SysState::setBloged(bool bloged)
{
    qDebug() << "SysState setBloged" << bloged;

    d->bloged = bloged;
}

// 吸样键使能状态
bool SysState::isAbsorbKeyEnabled() const
{
    // 根据IPU设定的状态，以及主机当前所处的状态决定
    return (d->absorbKeyState && this->isIdle() && !this->isShutdownFinished());
}

void SysState::setAbsorbKeyState(bool enable)
{
    qDebug() << "SysState setAbsorbKeyState" << enable;

    d->absorbKeyState = enable;
}

// 自动维护使能状态
bool SysState::isAutoMaintainEnabled() const
{
    // IPU允许进入休眠；管理员及其以下级别；开机完成状态；系统就绪状态；
    return d->autoMaintainState;
}

void SysState::setAutoMaintainState(bool enable)
{
    qDebug() << "SysState setAutoMaintainState" << enable;

    d->autoMaintainState = enable;
}