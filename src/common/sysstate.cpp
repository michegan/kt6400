#include <QtDebug>
#include <QStringList>

#include "sysstate.h"


class SysStatePrivate
{
public:
    SysStatePrivate();
    ~SysStatePrivate();

    // ��״̬
    quint32 getState();

    // ��״̬
    quint32 getSubState(quint32 mask);
    quint32 setSubState(quint32 state, quint32 mask);

public:
    // ��״̬
    quint32 state;

    // ��ǰģʽ��Ϣ
    Modes modes;

    // �¿�״̬
    bool bloged;

    // �����б�
    QList<int> faults;

    // ������ʹ��״̬
    bool absorbKeyState;

    // �Զ�ά��ʹ��״̬
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

// ��״̬
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
    // ԭ״̬
    quint32 oldState = this->getState();

    // ��״̬
    quint32 newState = ((oldState & ~mask) | (state & mask));
    qDebug() << "SysState setSubState" << QString::number(oldState, 16) << "->" << QString::number(newState, 16);

    // ���µ�ǰ״̬
    this->state = newState;

    // ����ԭ״̬
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

// ��״̬
quint32 SysState::state() const
{
    return d->state;
}

// ����״̬
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

    // ״̬�仯
    if (oldState != newState)
    {
        // ������״̬
        d->setSubState(newState, 0xFF00000);

        // ״̬�仯�ź�
        emit runStateChanged(oldState, newState);
    }
}

// ����״̬
quint32 SysState::faultState() const
{
    return d->getSubState(0x00FF0000);
}

void SysState::setFaultState(quint32 state)
{
    quint32 newState = state;
    quint32 oldState = this->faultState();

    // ״̬�仯
    if (oldState != newState)
    {
        // ������״̬
        d->setSubState(newState, 0x00FF0000);

        // ״̬�仯�ź�
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

        // ���ϱ仯�ź�
        emit faultChanged(d->faults);

        // ����״̬�仯
        this->setFaultState(SysState::StateFaultWarning);
    }
}

void SysState::relieveFault(int faultId)
{
    if (d->faults.contains(faultId))
    {
        d->faults.removeOne(faultId);

        // ���ϱ仯�ź�
        emit faultChanged(d->faults);

        // ����״̬�仯
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

// ���ػ�״̬
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

    // ״̬�仯
    if (oldState != newState)
    {
        // ������״̬
        d->setSubState(newState, 0x000000FF);
    
        // ״̬�仯�ź�
        emit startupStateChanged(oldState, newState);
    }
}

// ��ǰģʽ
Modes SysState::modes() const
{
    return d->modes;
}

void SysState::setModes(const Modes& modes)
{
    d->modes = modes;
}

// �¿�״̬
bool SysState::bloged() const
{
    return d->bloged;
}

void SysState::setBloged(bool bloged)
{
    qDebug() << "SysState setBloged" << bloged;

    d->bloged = bloged;
}

// ������ʹ��״̬
bool SysState::isAbsorbKeyEnabled() const
{
    // ����IPU�趨��״̬���Լ�������ǰ������״̬����
    return (d->absorbKeyState && this->isIdle() && !this->isShutdownFinished());
}

void SysState::setAbsorbKeyState(bool enable)
{
    qDebug() << "SysState setAbsorbKeyState" << enable;

    d->absorbKeyState = enable;
}

// �Զ�ά��ʹ��״̬
bool SysState::isAutoMaintainEnabled() const
{
    // IPU����������ߣ�����Ա�������¼��𣻿������״̬��ϵͳ����״̬��
    return d->autoMaintainState;
}

void SysState::setAutoMaintainState(bool enable)
{
    qDebug() << "SysState setAutoMaintainState" << enable;

    d->autoMaintainState = enable;
}