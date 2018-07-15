#ifndef _TIMESEQ_H_
#define _TIMESEQ_H_


#include <QTimer>
#include <QObject>

#include "libtimeseq.h"

class McuComm;


// ʱ��ִ��
class TIMESEQ_EXPORT Timeseq : public QObject
{
    Q_OBJECT

public:
    Timeseq();
    virtual ~Timeseq();

    // ִ������ΪseqNo��ʱ�򣬿����ǻ���ʱ��Ҳ�����ǹ���ʱ��
    bool runTimeseq(const QString& seqNo);

signals:
    // ���ݲɼ�����
    void dmaDataReady();

    // ʱ��ִ�н���
    void timeseqFinished(const QString& seqNo, bool result);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

    // �����ϱ�
    void onNewFault(int fault);

public:
    // ��ʼ��
    static void init();

    // ϡ��Һ������
    static bool hasDiluent();

    // ��Ѫ��������
    static bool hasLyse();

    // ��Һ������
    static bool isWasteFull();

    // ����������
    static bool buzzer(bool open);

    // �����ʼ��
    static bool motorHInit();
    static bool motorVInit();
    static bool motorSpInit();
    static bool motorVpInit();

    // ������
    static bool valve(quint8 vno, bool open);

private:
    // ʱ���
    QString seqNo;

    // ��ʱ��
    QTimer* timer;

    // MCUͨ��
    McuComm* mcuComm;
};


#endif // _TIMESEQ_H_
