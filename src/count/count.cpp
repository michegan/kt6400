#include <QFile>
#include <QDebug>

#include "dma.h"
#include "enum.h"
#include "user.h"
#include "count.h"
#include "cache.h"
#include "paras.h"
#include "newalg.h"
#include "faultid.h"
#include "seqfile.h"
#include "utility.h"
#include "libinter.h"
#include "paraname.h"
#include "algthread.h"
#include "machinexml.h"
#include "asynctimeseq.h"


class CountPrivate
{
public:
    CountPrivate();
    ~CountPrivate();

    // 保存原始数据
    void saveOrg();

    // 校准系数
    QMap<QString, float> getCalFactors();

    // 计数时序号
    QString countSeqNo(const SampleInfo& sampleInfo);

public:
    // 算法线程
    AlgThread* algThread;

    // 样本信息
    SampleInfo sampleInfo;

    // 计数状态
    bool isAlgFinished;
    bool isTimeseqFinished;

    // 时序执行
    AsyncTimeseq* timeseq;
};

CountPrivate::CountPrivate()
    : algThread(new AlgThread()), isAlgFinished(true), isTimeseqFinished(true), timeseq(new AsyncTimeseq())
{

}

CountPrivate::~CountPrivate()
{
    // 时序执行
    delete this->timeseq;

    // 算法线程
    delete this->algThread;
}

// 保存原始数据
void CountPrivate::saveOrg()
{
    do 
    {
        // DMA数据缓冲区
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (0 == dmaBuf)
        {
            qWarning() << "CountPrivate saveOrg getDmaBuf fail";
            break;
        }

        // WBC通道ORG文件
        {
            QString fileName = "./wbc.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "Alg saveOrg open fail";
                break;
            }

            // 写入DMA数据
            qint64 len = file.write(dmaBuf->pWbcSamplingBuf, dmaBuf->wbcSamplingBufLen);
            if (len != dmaBuf->wbcSamplingBufLen)
            {
                qWarning() << "CountPrivate saveOrg write fail";
                break;
            }

            file.close();
        }

        // RBC通道ORG文件
        {
            QString fileName = "./rbc.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "CountPrivate saveOrg open fail";
                break;
            }

            // 写入DMA数据
            qint64 len = file.write(dmaBuf->pRbcSamplingBuf, dmaBuf->rbcSamplingBufLen);
            if (len != dmaBuf->rbcSamplingBufLen)
            {
                qWarning() << "CountPrivate saveOrg write fail";
                break;
            }

            file.close();
        }

        // PLT通道ORG文件
        {
            QString fileName = "./plt.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "CountPrivate saveOrg open fail";
                break;
            }

            // 写入DMA数据
            qint64 len = file.write(dmaBuf->pPltSamplingBuf, dmaBuf->pltSamplingBufLen);
            if (len != dmaBuf->pltSamplingBufLen)
            {
                qWarning() << "CountPrivate saveOrg write fail";
                break;
            }

            file.close();
        }

    } while (0);
}

// 校准系数
QMap<QString, float> CountPrivate::getCalFactors()
{
    QMap<QString, float> calFactors;

    QStringList paras = Paras::calibrateParaNames();
    foreach (QString para, paras)
    {
        float value = Cache::getCalFactor(this->sampleInfo.modes, para);
        calFactors.insert(para, value);
    }

    return calFactors;
}

// 计数时序号
QString CountPrivate::countSeqNo(const SampleInfo& sampleInfo)
{
    const Modes& modes = sampleInfo.modes;

    MachineXml xml;
    if (xml.load())
    {
        int speed = xml.getFloatValue2(KEY1_MACHINE, KEY2_TEST_SPEED);
        int diluent = xml.getFloatValue2(KEY1_MACHINE, KEY2_DILUENT_FACTOR);
        int lyse = xml.getFloatValue2(KEY1_MACHINE, KEY2_LYSE_VOLUME);

        return SeqFile::countSeqNo(modes, speed, diluent, lyse);
    }
    else
    {
        return "";
    }
}


Count::Count()
    : d(new CountPrivate())
{
    // 关联信号槽
    connect(d->algThread, SIGNAL(finished()), this, SLOT(onAlgFinished()));

    connect(d->timeseq, SIGNAL(dmaDataReady()), this, SLOT(onDmaDataReady()));
    connect(d->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

Count::~Count()
{
    delete d;
}

// 启动计数
int Count::startCount(const SampleInfo& sampleInfo, float* countTime)
{
    // 时序号
    QString seqNo = d->countSeqNo(sampleInfo);
    if (seqNo.isEmpty())
    {
        return EXIT_FAIL;
    }

    // 执行时序
    int ret = d->timeseq->runTimeseq(seqNo);
    if (EXIT_OK == ret)
    {
        // 算法初始化
        Alg::init();
        Dma::init();

        // 更新计数状态
        d->isAlgFinished = false;
        d->isTimeseqFinished = false;

        d->sampleInfo = sampleInfo;
        
        // 计数时间
        if (countTime)
        {
            *countTime = SeqFile::getSeqTime(seqNo);
        }
    }

    return ret;
}

// 算法结果
HistInfo Count::wbcHist() const
{
    return Alg::wbcHist();
}

HistInfo Count::rbcHist() const
{
    return Alg::rbcHist();
}

HistInfo Count::pltHist() const
{
    return Alg::pltHist();
}

ParaList Count::paraResult() const
{
    return Alg::paraResult();
}

// 算法结束
void Count::onAlgFinished()
{
    SysState* sysState = Cache::sysState();
    if (sysState)
    {
        sysState->setFault(FAULT_WBC_CLOG, Alg::wbcClog());
        sysState->setFault(FAULT_RBC_CLOG, Alg::rbcClog());
        sysState->setFault(FAULT_HGB_ERROR, Alg::hgbError());
        sysState->setFault(FAULT_HGB_BUBBLE, Alg::hgbBubble());
    }

    ParaList paraResult = this->paraResult();
    paraResult.output();

    HistInfo histInfo = this->wbcHist();
    histInfo.output();

    histInfo = this->rbcHist();
    histInfo.output();

    histInfo = this->pltHist();
    histInfo.output();

    // 更新计数状态
    d->isAlgFinished = true;

    // 算法结束
    emit algFinished();

    // 算法和时序都结束，则本次计数结束
    if (d->isTimeseqFinished)
    {
        // 计数结束信号
        emit countFinished(true);
    }
    else
    {
        // 等待时序结束
        qDebug() << "Count onDmaDataReady isTimeseqFinished" << d->isTimeseqFinished;
    }
}

// 数据采集结束
void Count::onDmaDataReady()
{
    qDebug() << "Count onDmaDataReady";

    // 算法设置
    unsigned short t200 = 0;

    const User* user = Cache::currentUser();

    Alg::setSysEvtBuf(t200, 0);
    Alg::setSysInfo(1, 1, 90, 120);

    QMap<QString, float> calFactors = d->getCalFactors();
    Alg::setCal(calFactors.value(PARA_WBC, 1.0),  calFactors.value(PARA_RBC, 1.0), calFactors.value(PARA_HGB, 1.0),
                calFactors.value(PARA_MCV, 1.0), calFactors.value(PARA_PLT, 1.0));

    Alg::setMaintanceVal(90, 125, 85, 117, 50, 50, 50, 50, 125, 125);

    // 算法计算
    Alg::setModes(d->sampleInfo.modes);

#ifndef _WIN32
    // DMA数据处理
    DmaBuf* dmaBuf = Dma::getDmaBuf();
    if (dmaBuf)
    {
        SYS_AD_BUF* pSysAdBuf = (SYS_AD_BUF*)GetSysAdBuf();
        if (pSysAdBuf)
        {
            dmaBuf->wbcSamplingBufLen = pSysAdBuf->ad_buf[0];
            dmaBuf->rbcSamplingBufLen = pSysAdBuf->ad_buf[1];
            dmaBuf->pltSamplingBufLen = pSysAdBuf->ad_buf[2];
        }
        qDebug() << "Count onDmaDataReady" << dmaBuf->wbcSamplingBufLen << dmaBuf->rbcSamplingBufLen << dmaBuf->pltSamplingBufLen;
    }

    // 算法原始数据保存
    // d->saveOrg();
#endif

    // 算法计算
    d->algThread->start();
}

// 时序结束
void Count::onTimeseqFinished(const QString& seqNo, bool result)
{
    qDebug() << "Count onTimeseqFinished" << seqNo << result;

#ifdef _WIN32
    // 算法处理
    this->onDmaDataReady();
#endif

    // 更新计数状态
    d->isTimeseqFinished = true;

    // 算法和时序都结束，则本次计数结束
    if (d->isAlgFinished)
    {
        // 计数结束信号
        emit countFinished(result);
    }
    else
    {
        // 等待算法结束
        qDebug() << "Count onTimeseqFinished isAlgFinished" << d->isAlgFinished;
    }
}