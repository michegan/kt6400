#ifndef _SYS_STATE_H_
#define _SYS_STATE_H_


#include <QObject>

#include "modes.h"
#include "libcommon.h"


class SysStatePrivate;


// ϵͳ״̬
class COMMON_EXPORT SysState : public QObject
{
    Q_OBJECT

public:
    // ��״̬
    enum RunState
    {
        StateReady = 0x01000000, // ����״̬
        StateRunning = 0x02000000, // ����״̬
        StateSleeping = 0x04000000, // ����״̬
    };

    // ����״̬
    enum FaultState
    {
        StateFaultNone = 0x00010000, // �޹���״̬
        StateFaultInformation = 0x00020000, // ���ڹ���״̬����ʾ����ϣ�
        StateFaultWarning = 0x00040000, // ���ڹ���״̬����������ϣ�
        StateFaultCritical = 0x00080000, // ���ڹ���״̬����������ϣ�
    };

    // ����״̬
    enum StartupShutdownState
    {
        StateStaruping0 = 0x00000001, // ������״̬��ϵͳ���ã���ѹ�Լ�׶Σ�
        StateStaruping1 = 0x00000002, // ������״̬���¶��Լ죬ѹ���Լ죬Һ·��ʼ���׶Σ�
        StateStaruping2 = 0x00000004, // ������״̬��������ϴ��
        StateStaruping3 = 0x00000008, // ������״̬�����ײ����׶Σ�

        StateStartupFinished = 0x00000020, // �������
        StateShutdowning = 0x00000040, // �ػ���״̬
        StateShutdownFinished = 0x00000080, // �ػ����״̬
    };

public:
    SysState();
    virtual ~SysState();

    // ��״̬
    quint32 state() const;

    // ����״̬
    bool isIdle() const;
    bool isSleeping() const;

    quint32 runState() const;
    void setRunState(quint32 state);

    // ����״̬
    quint32 faultState() const;
    void setFaultState(quint32 state);

    QList<int> faultList() const;

    void raiseFault(int faultId);
    void relieveFault(int faultId);

    void setFault(int fault, bool bfault);

    // ���ػ�״̬
    bool isStartupFinished() const;
    bool isShutdownFinished() const;

    quint32 startupShutdownState() const;
    void setStartupShutdownState(quint32 state);

public:
    // ��ǰģʽ
    Modes modes() const;
    void setModes(const Modes& modes);

    // �¿�״̬
    bool bloged() const;
    void setBloged(bool bloged);

    // ������ʹ��״̬
    bool isAbsorbKeyEnabled() const;
    void setAbsorbKeyState(bool enable);

    // �Զ�ά��ʹ��״̬
    bool isAutoMaintainEnabled() const;
    void setAutoMaintainState(bool enable);

signals:
    // ������״̬�仯
    void absorbKeyStateChanged(bool enable);

    // �Զ�ά��״̬�仯
    void autoMaintainStateChanged(bool enable);

    // ���ϱ仯
    void faultChanged(const QList<int>& faults);

    // ϵͳ״̬�仯
    void runStateChanged(quint32 oldState, quint32 newState);
    void faultStateChanged(quint32 oldState, quint32 newState);
    void startupStateChanged(quint32 oldState, quint32 newState);

private:
    SysStatePrivate* d;
};


#endif // _SYS_STATE_H_