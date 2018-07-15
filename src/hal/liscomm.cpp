#include <QMutex>
#include <QtDebug>

#include "hal.h"
#include "define.h"
#include "liscomm.h"
#include "utility.h"
#include "paraname.h"
#include "qextserialport.h"


LisComm::LisComm()
    : QThread(), mutex(0), serial(0)
{
    // ��ͨ��������
    this->mutex = new QMutex();

    // ͨ�Ŵ���
    this->serial = new QextSerialPort("/dev/ttySAC0");
    if (this->serial)
    {
        if (this->serial->open(QIODevice::ReadWrite))
        {
            this->serial->setDataBits(DATA_8);
            this->serial->setParity(PAR_NONE);
            this->serial->setStopBits(STOP_1);
            this->serial->setBaudRate(BAUD9600);
            this->serial->setFlowControl(FLOW_OFF);
            this->serial->setTimeout(5, 0);

            qDebug() << "LisComm LisComm open success";
        }
        else
        {
            qWarning() << "LisComm LisComm open fail";
        }
    }
    else
    {
        qWarning() << "LisComm LisComm new fail";
    }
}

LisComm::~LisComm()
{
    // ��ͨ��������
    this->mutex->lock();

    this->lowLimits.clear();
    this->highLimits.clear();
    this->paraResults.clear();
    this->sampleInfos.clear();

    this->mutex->unlock();

    delete this->mutex;

    // ͨ�Ŵ���
    if (this->serial)
    {
        delete this->serial;
        this->serial = 0;
    }
}

// ��������
QString LisComm::sendQcSample(const SampleInfo& sampleInfo, const ParaList& paraResult)
{
    return this->sendNormalSample(sampleInfo, paraResult, ParaList(), ParaList());
}

QString LisComm::sendNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits)
{
    this->mutex->lock();

    QString guid = Utility::newGuid();

    this->guids.append(guid);
    this->lowLimits.insert(guid, lowLimits);
    this->highLimits.insert(guid, highLimits);
    this->paraResults.insert(guid, paraResult);
    this->sampleInfos.insert(guid, sampleInfo);

    this->mutex->unlock();

    return guid;
}

// �߳�ִ����
void LisComm::run()
{
    while (1)
    {
        if (this->guids.isEmpty())
        {
            // ��������գ�������ȴ�
            Utility::ssleep(2);
        }
        else
        {
            this->mutex->lock();

            // ��ȡ��һ������������
            QString guid = this->guids.first();
            ParaList lowLimits = this->lowLimits.take(guid);
            ParaList highLimits = this->highLimits.take(guid);
            ParaList paraResult = this->paraResults.take(guid);
            SampleInfo sampleInfo = this->sampleInfos.take(guid);

            this->mutex->unlock();

            // �����������ʿ����������ִ������
            QByteArray byteArray;
            if (BLOOD_MODE_QC == sampleInfo.workMode())
            {
                byteArray = this->packQCSample(sampleInfo, paraResult);
            }
            else
            {
                byteArray = this->packNormalSample(sampleInfo, paraResult, lowLimits, highLimits);
            }

            // ��������
            int ret = this->serial->write(byteArray);
            emit sendFinished(guid, (ret == byteArray.length()));
        }
    }
}


// ���һ������
QByteArray LisComm::packQCSample(const SampleInfo& sampleInfo, const ParaList& paraResult)
{
    // ���ݴ��
    QByteArray byteArray;

    byteArray.append('@'); // ֡ͷ
    byteArray.append('a');
    byteArray.append('\0');

    QString sampleId = sampleInfo.sampleId; // �������
    byteArray.append(QString("%1").arg(sampleId, MAX_SID_LEN, Qt::Key_0));

    QDateTime testTime = sampleInfo.testTime; // ����ʱ��
    byteArray.append(testTime.toString("yyyyMMddhhmm") + "00");

    // WBC RBC PLT HGB HCT MCV MCH MCHC LYM# GRAN# LYM% GRAN%
    QStringList paras;
    paras << PARA_MID_PER << PARA_MID_NUM << PARA_MPV << PARA_PLCC << PARA_PLCR << PARA_RDW_CV << PARA_RDW_SD;

    byteArray.append(QString("%1").arg(sampleInfo.fileNo, MAX_SID_LEN, Qt::Key_0)); // �ļ���
    byteArray.append('H');

    byteArray.append('&'); // ֡β

    return byteArray;
}

QByteArray LisComm::packNormalSample(const SampleInfo& sampleInfo, const ParaList& paraResult, const ParaList& lowLimits, const ParaList& highLimits)
{
    // ���ݴ��
    QByteArray byteArray;

    byteArray.append('@'); // ֡ͷ
    byteArray.append('a');
    byteArray.append('\0');

    QString sampleId = sampleInfo.sampleId; // �������
    byteArray.append(QString("%1").arg(sampleId, MAX_SID_LEN, Qt::Key_0));

    QDateTime testTime = sampleInfo.testTime; // ����ʱ��
    byteArray.append(testTime.toString("yyyyMMddhhmm") + "00");

    byteArray.append(QString(0, QChar('#'))); // ��һ��Ԥ������
    byteArray.append(QString(9, QChar('#'))); // �ڶ���Ԥ������
    byteArray.append(QString(8, QChar('#'))); // ������Ԥ������

    for (int i = 0; i < 4; i++) // WBCֱ��ͼ����
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }

    for (int i = 0; i < 4; i++) // WBCֱ��ͼ������
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }
    for (int i = 0; i < 2; i++) // RBCֱ��ͼ������
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }
    for (int i = 0; i < 2; i++) // PLTֱ��ͼ������
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }

    for (int i = 0; i < 256; i++) // WBCֱ��ͼ
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }
    for (int i = 0; i < 256; i++) // RBCֱ��ͼ
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }
    for (int i = 0; i < 128; i++) // PLTֱ��ͼ
    {
        byteArray.append(QString("%1").arg(i, 3, Qt::Key_0));
    }


    byteArray.append('&'); // ֡β

    return byteArray;
}
