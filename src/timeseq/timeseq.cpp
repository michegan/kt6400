#include <QFile>
#include <QtDebug>

#include "hal.h"
#include "mcucomm.h"
#include "seqfile.h"
#include "timeseq.h"
#include "reagent.h"


// 通信线程
static McuComm* s_mcuComm = 0;


Timeseq::Timeseq()
    : seqNo(""), timer(new QTimer()), mcuComm(s_mcuComm)
{
    // 单次触发
    this->timer->setSingleShot(true);

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(this->mcuComm, SIGNAL(dmaDataReady()), this, SIGNAL(dmaDataReady()));
}

Timeseq::~Timeseq()
{
    // 定时器
    delete this->timer;
}

// 执行时序（同步）
bool Timeseq::runTimeseq(const QString& seqNo)
{
    bool ret = false;

    // 时序文件名
    QString fileName = "./timeseq/" + seqNo + ".dat";
    qDebug() << "Timeseq runTimeseq" << fileName;

    // 打开文件，读取全部时序指令，下发给MCU
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {    
        QByteArray dataArray = file.readAll();
        ret = (this->mcuComm ? this->mcuComm->write(dataArray) : false);
        qDebug() << "Timeseq runTimeseq write" << ret;

        // 时序包下发成功，启动时序定时器
        if (ret)
        {
            // 记录时序信息
            this->seqNo = seqNo;

            // 定时等待时序结束
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

// 定时器超时
void Timeseq::onTimerOut()
{
    // 试剂消耗
    QList<int> reagents = Reagent::reagents();
    foreach (int reagent, reagents)
    {
        float consume = SeqFile::getSeqReagent(this->seqNo, reagent);
        Reagent::consume(reagent, consume);
    }

    // 时序正常结束
    qDebug() << "Timeseq onTimerOut" << this->seqNo;
    emit timeseqFinished(this->seqNo, true);
}

// 故障上报
void Timeseq::onNewFault(int fault)
{
    // 停止计时
    this->timer->stop();

    // 时序异常结束
    emit timeseqFinished(this->seqNo, false);
}

// 初始化
void Timeseq::init()
{
    qDebug() << "Timeseq init";

    // MCU通信
    s_mcuComm = new McuComm();
    if (s_mcuComm)
    {
        s_mcuComm->start();
    }
}

// 稀释液传感器
bool Timeseq::hasDiluent()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append(0x01);

    // 发送数据，并处理应答
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

// 溶血剂传感器
bool Timeseq::hasLyse()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append((char)0x00);

    // 发送数据，并处理应答
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

// 废液传感器
bool Timeseq::isWasteFull()
{
    QByteArray dataArray;

    dataArray.append(0x60);
    dataArray.append(0x03);

    // 发送数据，并处理应答
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

// 蜂鸣器开关
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

// 电机初始化
bool Timeseq::motorHInit()
{
    QByteArray dataArray;

    dataArray.append(0x50);
    dataArray.append(0x10);
    dataArray.append(5); // A：05；B：14；C：12；D：14
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
    dataArray.append(14); // A：05；B：14；C：12；D：14
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
    dataArray.append(12); // A：05；B：14；C：12；D：14
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
    dataArray.append(14); // A：05；B：14；C：12；D：14
    dataArray.append(0x08);
    dataArray.append(0x03);

    bool ret = (s_mcuComm && s_mcuComm->post(dataArray));

    qDebug() << "Timeseq motorVpInit" << ret;

    return ret;
}

// 阀开关
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