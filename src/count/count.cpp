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

    // ����ԭʼ����
    void saveOrg();

    // У׼ϵ��
    QMap<QString, float> getCalFactors();

    // ����ʱ���
    QString countSeqNo(const SampleInfo& sampleInfo);

public:
    // �㷨�߳�
    AlgThread* algThread;

    // ������Ϣ
    SampleInfo sampleInfo;

    // ����״̬
    bool isAlgFinished;
    bool isTimeseqFinished;

    // ʱ��ִ��
    AsyncTimeseq* timeseq;
};

CountPrivate::CountPrivate()
    : algThread(new AlgThread()), isAlgFinished(true), isTimeseqFinished(true), timeseq(new AsyncTimeseq())
{

}

CountPrivate::~CountPrivate()
{
    // ʱ��ִ��
    delete this->timeseq;

    // �㷨�߳�
    delete this->algThread;
}

// ����ԭʼ����
void CountPrivate::saveOrg()
{
    do 
    {
        // DMA���ݻ�����
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (0 == dmaBuf)
        {
            qWarning() << "CountPrivate saveOrg getDmaBuf fail";
            break;
        }

        // WBCͨ��ORG�ļ�
        {
            QString fileName = "./wbc.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "Alg saveOrg open fail";
                break;
            }

            // д��DMA����
            qint64 len = file.write(dmaBuf->pWbcSamplingBuf, dmaBuf->wbcSamplingBufLen);
            if (len != dmaBuf->wbcSamplingBufLen)
            {
                qWarning() << "CountPrivate saveOrg write fail";
                break;
            }

            file.close();
        }

        // RBCͨ��ORG�ļ�
        {
            QString fileName = "./rbc.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "CountPrivate saveOrg open fail";
                break;
            }

            // д��DMA����
            qint64 len = file.write(dmaBuf->pRbcSamplingBuf, dmaBuf->rbcSamplingBufLen);
            if (len != dmaBuf->rbcSamplingBufLen)
            {
                qWarning() << "CountPrivate saveOrg write fail";
                break;
            }

            file.close();
        }

        // PLTͨ��ORG�ļ�
        {
            QString fileName = "./plt.org";
            qDebug() << "CountPrivate saveOrg" << fileName;

            QFile file(fileName);
            if (!file.open(QIODevice::Truncate | QIODevice::ReadWrite))
            {
                qWarning() << "CountPrivate saveOrg open fail";
                break;
            }

            // д��DMA����
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

// У׼ϵ��
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

// ����ʱ���
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
    // �����źŲ�
    connect(d->algThread, SIGNAL(finished()), this, SLOT(onAlgFinished()));

    connect(d->timeseq, SIGNAL(dmaDataReady()), this, SLOT(onDmaDataReady()));
    connect(d->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));
}

Count::~Count()
{
    delete d;
}

// ��������
int Count::startCount(const SampleInfo& sampleInfo, float* countTime)
{
    // ʱ���
    QString seqNo = d->countSeqNo(sampleInfo);
    if (seqNo.isEmpty())
    {
        return EXIT_FAIL;
    }

    // ִ��ʱ��
    int ret = d->timeseq->runTimeseq(seqNo);
    if (EXIT_OK == ret)
    {
        // �㷨��ʼ��
        Alg::init();
        Dma::init();

        // ���¼���״̬
        d->isAlgFinished = false;
        d->isTimeseqFinished = false;

        d->sampleInfo = sampleInfo;
        
        // ����ʱ��
        if (countTime)
        {
            *countTime = SeqFile::getSeqTime(seqNo);
        }
    }

    return ret;
}

// �㷨���
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

// �㷨����
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

    // ���¼���״̬
    d->isAlgFinished = true;

    // �㷨����
    emit algFinished();

    // �㷨��ʱ�򶼽������򱾴μ�������
    if (d->isTimeseqFinished)
    {
        // ���������ź�
        emit countFinished(true);
    }
    else
    {
        // �ȴ�ʱ�����
        qDebug() << "Count onDmaDataReady isTimeseqFinished" << d->isTimeseqFinished;
    }
}

// ���ݲɼ�����
void Count::onDmaDataReady()
{
    qDebug() << "Count onDmaDataReady";

    // �㷨����
    unsigned short t200 = 0;

    const User* user = Cache::currentUser();

    Alg::setSysEvtBuf(t200, 0);
    Alg::setSysInfo(1, 1, 90, 120);

    QMap<QString, float> calFactors = d->getCalFactors();
    Alg::setCal(calFactors.value(PARA_WBC, 1.0),  calFactors.value(PARA_RBC, 1.0), calFactors.value(PARA_HGB, 1.0),
                calFactors.value(PARA_MCV, 1.0), calFactors.value(PARA_PLT, 1.0));

    Alg::setMaintanceVal(90, 125, 85, 117, 50, 50, 50, 50, 125, 125);

    // �㷨����
    Alg::setModes(d->sampleInfo.modes);

#ifndef _WIN32
    // DMA���ݴ���
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

    // �㷨ԭʼ���ݱ���
    // d->saveOrg();
#endif

    // �㷨����
    d->algThread->start();
}

// ʱ�����
void Count::onTimeseqFinished(const QString& seqNo, bool result)
{
    qDebug() << "Count onTimeseqFinished" << seqNo << result;

#ifdef _WIN32
    // �㷨����
    this->onDmaDataReady();
#endif

    // ���¼���״̬
    d->isTimeseqFinished = true;

    // �㷨��ʱ�򶼽������򱾴μ�������
    if (d->isAlgFinished)
    {
        // ���������ź�
        emit countFinished(result);
    }
    else
    {
        // �ȴ��㷨����
        qDebug() << "Count onTimeseqFinished isAlgFinished" << d->isAlgFinished;
    }
}