#include <QFile>
#include <QtDebug>

#include "hal.h"
#include "mcucomm.h"
#include "seqfile.h"
#include "timeseq.h"
#include "reagent.h"


// ͨ���߳�
static McuComm* s_mcuComm = 0;


Timeseq::Timeseq()
    : seqNo(""), timer(new QTimer()), mcuComm(s_mcuComm)
{
    // ���δ���
    this->timer->setSingleShot(true);

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(this->mcuComm, SIGNAL(dmaDataReady()), this, SIGNAL(dmaDataReady()));
}

Timeseq::~Timeseq()
{
    // ��ʱ��
    delete this->timer;
}

// ִ��ʱ��ͬ����
bool Timeseq::runTimeseq(const QString& seqNo)
{
    bool ret = false;

    // ʱ���ļ���
    QString fileName = "./timeseq/" + seqNo + ".dat";
    qDebug() << "Timeseq runTimeseq" << fileName;

    // ���ļ�����ȡȫ��ʱ��ָ��·���MCU
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {    
        QByteArray dataArray = file.readAll();
        ret = (this->mcuComm ? this->mcuComm->write(dataArray) : false);
        qDebug() << "Timeseq runTimeseq write" << ret;

        // ʱ����·��ɹ�������ʱ��ʱ��
        if (ret)
        {
            // ��¼ʱ����Ϣ
            this->seqNo = seqNo;

            // ��ʱ�ȴ�ʱ�����
            float time = SeqFile::getSeqTime(seqNo);
            qDebug() << "Timeseq runTimeseq time" << time;

            this->timer->start(time * 1000);
        }

        file.close();
    }
    else
    {
        qWarning() << "Timeseq runTimeseq open fail" << fileName;
    }

    return ret;
}

// ��ʱ����ʱ
void Timeseq::onTimerOut()
{
    // �Լ�����
    QList<int> reagents = Reagent::reagents();
    foreach (int reagent, reagents)
    {
        float consume = SeqFile::getSeqReagent(this->seqNo, reagent);
        Reagent::consume(reagent, consume);
    }

    // ʱ����������
    qDebug() << "Timeseq onTimerOut" << this->seqNo;
    emit timeseqFinished(this->seqNo, true);
}

// �����ϱ�
void Timeseq::onNewFault(int fault)
{
    // ֹͣ��ʱ
    this->timer->stop();

    // ʱ���쳣����
    emit timeseqFinished(this->seqNo, false);
}

// ��ʼ��
void Timeseq::init()
{
    qDebug() << "Timeseq init";

    // MCUͨ��
    s_mcuComm = new McuComm();
    if (s_mcuComm)
    {
        s_mcuComm->start();
    }
}

// ϡ��Һ������
bool Timeseq::hasDiluent()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append(0x01);

    // �������ݣ�������Ӧ��
    char state = 0;
    bool has = false;

    bool ret = (s_mcuComm && s_mcuComm->query(dataArray, &state));
    if (ret)
    {
        has = (1 == state); 
    }

    qDebug() << "Timeseq hasDiluent" << ret << has;

    return has;
}

// ��Ѫ��������
bool Timeseq::hasLyse()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append((char)0x00);

    // �������ݣ�������Ӧ��
    char state = 0;
    bool has = false;

    bool ret = (s_mcuComm && s_mcuComm->query(dataArray, &state));
    if (ret)
    {
        has = (1 == state); 
    }

    qDebug() << "Timeseq hasLyse" << ret << has;

    return has;
}

// ��Һ������
bool Timeseq::isWasteFull()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append(0x03);

    // �������ݣ�������Ӧ��
    char state = 0;
    bool full = true;

    bool ret = (s_mcuComm && s_mcuComm->query(dataArray, &state));
    if (ret)
    {
        full = (1 == state); 
    }

    qDebug() << "Timeseq isWasteFull" << ret << full;

    return full;
}

// ����������
bool Timeseq::buzzer(bool open)
{
    QByteArray dataArray;

    dataArray.append(0x11);
    dataArray.append(0x20);
    dataArray.append(open ? 0x10 : 0x11);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq buzzer" << open << ret;

    return ret;
}

// �����ʼ��
bool Timeseq::motorHInit()
{
    QByteArray dataArray;

    dataArray.append(0x50);
    dataArray.append(0x10);
    dataArray.append(5); // A��05��B��14��C��12��D��14
    dataArray.append(0x08);
    dataArray.append(0x03);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq motorHInit" << ret;

    return ret;
}

bool Timeseq::motorVInit()
{
    QByteArray dataArray;

    dataArray.append(0x51);
    dataArray.append(0x10);
    dataArray.append(14); // A��05��B��14��C��12��D��14
    dataArray.append(0x08);
    dataArray.append(0x03);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq motorVInit" << ret;

    return ret;
}

bool Timeseq::motorSpInit()
{
    QByteArray dataArray;

    dataArray.append(0x20);
    dataArray.append(0x20);
    dataArray.append(12); // A��05��B��14��C��12��D��14
    dataArray.append(0x08);
    dataArray.append(0x03);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq motorSpInit" << ret;

    return ret;
}

bool Timeseq::motorVpInit()
{
    QByteArray dataArray;

    dataArray.append(0x28);
    dataArray.append(0x20);
    dataArray.append(14); // A��05��B��14��C��12��D��14
    dataArray.append(0x08);
    dataArray.append(0x03);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq motorVpInit" << ret;

    return ret;
}

// ������
bool Timeseq::valve(quint8 vno, bool open)
{
    QByteArray dataArray;

    dataArray.append(0x11);
    dataArray.append(0x03);
    dataArray.append(((open ? 0x1 : 0x0) << 7) | vno);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq valve" << vno << open << ret;

    return ret;
}