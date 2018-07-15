#include <QtDebug>
#include <QPainter>

#include "enum.h"
#include "cache.h"
#include "count.h"
#include "faultid.h"
#include "seqfile.h"
#include "countwin.h"
#include "paraname.h"
#include "refrange.h"
#include "resource.h"
#include "sysstate.h"
#include "startupwin.h"
#include "shutdownxml.h"
#include "asynctimeseq.h"
#include "reviewsampletable.h"


StartupWin::StartupWin(QWidget* parent)
    : FuncWin(parent), timer(new QTimer(this)), count(new Count()), timeseq(new AsyncTimeseq())
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ���ڱ�ʶ
    this->setWId("StartupWin");

    // ������Ϣ
    this->sampleInfo.sampleId = "BACKGROUND";

    this->sampleInfo.modes.workMode = WORK_MODE_BACKGROUND;
    this->sampleInfo.modes.analysisMode = ANALYSIS_MODE_CBC;
    this->sampleInfo.modes.bloodMode = BLOOD_MODE_BACKGROUND;

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(this->count, SIGNAL(algFinished()), this, SLOT(onCountAlgFinished()));
    connect(this->count, SIGNAL(countFinished(bool)), this, SLOT(onCountFinished(bool)));

    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));

    // ���뿪������
    QTimer::singleShot(200, this, SLOT(onStartupTimeOut()));
}

StartupWin::~StartupWin()
{
    // ��������
    delete this->count;

    // ʱ��ִ����
    delete this->timeseq;
}

// �����ַ���
void StartupWin::setWindowText()
{
    // ���ദ��
    // FuncWin::setWindowText();

    // ���ദ��
}

// �¼�����
void StartupWin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // ���Ʊ���ͼ
    const QImage* image = Resource::image("big_logo");
    if (image)
    {
        painter.drawImage(150, 0, *image);
    }

    // ���ദ��
    FuncWin::paintEvent(event);
}

// ��ʱ����ʱ
void StartupWin::onTimerOut()
{
    int value = ui.pbProgress->value();
    ui.pbProgress->setValue(value + 1);
}

void StartupWin::onStartupTimeOut()
{
    // �Լ����


    // ����ϵͳ״̬
    this->setStartupState(SysState::StateStaruping0);


    // ����Һ·��ʼ��
    QString seqNo = SeqFile::initSeqNo();

    int ret = this->timeseq->runTimeseq(seqNo);
    if (EXIT_OK == ret)
    {
        // ������ʾ
        this->setText(ui.lbNote, "IDS_LIQUID_INIT");

        // ��������
        float time = SeqFile::getSeqTime(seqNo);
        ui.pbProgress->setValue(0);
        ui.pbProgress->setMaximum(time);

        this->timer->start(1000);
    }
    else
    {
        // ��������
        this->onStartupFinished();
    }
}

// �㷨����
void StartupWin::onCountAlgFinished()
{
    do 
    {
        // �������
        ParaList paraResult = this->count->paraResult();

        // �����������ݿ�
        ReviewSampleTable* sampleTable = ReviewSampleTable::instance();
        if (0 == sampleTable)
        {
            qWarning() << "StartupWin onCountAlgFinished instance fail";
            break;
        }

        int fid = 0;
        if (!sampleTable->addSample(fid, this->sampleInfo, paraResult))
        {
            qWarning() << "StartupWin onCountAlgFinished addSample fail";
            break;
        }

        HistInfo wbcHist = this->count->wbcHist();
        HistInfo rbcHist = this->count->rbcHist();
        HistInfo pltHist = this->count->pltHist();

        if (!sampleTable->updateSample(fid, wbcHist, rbcHist, pltHist))
        {
            qWarning() << "StartupWin onCountAlgFinished updateSample fail";
            break;
        }


        // �󶨲ο���Χ
        ParaList lowLimits;
        ParaList highLimits;
        if (RefRange::getLimits(this->sampleInfo, lowLimits, highLimits))
        {
            paraResult.setLimits(lowLimits, highLimits);
        }
        else
        {
            qWarning() << "StartupWin onCountAlgFinished getLimits fail";
        }

        // ���׷�Χ���
        int wbcFlag = paraResult.paraFlag(PARA_WBC);
        int rbcFlag = paraResult.paraFlag(PARA_RBC);
        int pltFlag = paraResult.paraFlag(PARA_PLT);
        int hgbFlag = paraResult.paraFlag(PARA_HGB);

        if (wbcFlag != PARA_NORMAL_FLAG || rbcFlag != PARA_NORMAL_FLAG || pltFlag != PARA_NORMAL_FLAG || hgbFlag != PARA_NORMAL_FLAG)
        {
            SysState* sysState = Cache::sysState();
            sysState->raiseFault(FAULT_BACKGROUND);
        }
    } while (0);
}

// ��������
void StartupWin::onCountFinished(bool result)
{
    // ��������
    this->onStartupFinished();
}

// ʱ�����
void StartupWin::onTimeseqFinished(const QString& seqNo, bool result)
{
    // ֹͣ��ʱ��
    this->timer->stop();

    // ʱ�����
    ui.pbProgress->setValue(ui.pbProgress->maximum());

    if (result)
    {
        // Һ·��ʼ������
        if (SeqFile::initSeqNo() == seqNo)
        {
            // ������ϴ
            QString nextSeqNo = SeqFile::startingUpSeqNo();

            ShutdownXml xml;
            if (xml.load())
            {
                QString type = xml.getTextValue2(KEY1_SHUTDOWN, KEY2_SHUTDOWN_TYPE);
                if (VALUE_SHUTDOWN_PACKAGE == type)
                {
                    nextSeqNo = SeqFile::wholeFillSeqNo();
                }
            }

            // ����������ϴ
            int ret = this->timeseq->runTimeseq(nextSeqNo);
            if (EXIT_OK == ret)
            {
                // ������ʾ
                this->setText(ui.lbNote, "IDS_LIQUID_CLEANUP");

                // ��������
                float time = SeqFile::getSeqTime(seqNo);
                ui.pbProgress->setValue(0);
                ui.pbProgress->setMaximum(time);

                this->timer->start(1000);

                // ����ϵͳ״̬
                this->setStartupState(SysState::StateStaruping1);
            }
            else
            {
                // ��������
                this->onStartupFinished();
            }
        }
        // ������ϴ����
        else if (SeqFile::startingUpSeqNo() == seqNo || SeqFile::wholeFillSeqNo() == seqNo)
        {
            // ���Ĺػ�����
            ShutdownXml xml;
            if (xml.load())
            {
                xml.setTextValue2(KEY1_SHUTDOWN, KEY2_SHUTDOWN_TYPE, VALUE_SHUTDOWN_ABNORMAL);
                xml.save();
            }

            // ����ϵͳ״̬
            this->setStartupState(SysState::StateStaruping2);

            // �������׼���
            float time = 0;
            int ret = this->count->startCount(this->sampleInfo, &time);
            if (EXIT_OK == ret)
            {
                // ������ʾ
                this->setText(ui.lbNote, "IDS_BACKGROUND_TEST");

                // ��������
                ui.pbProgress->setValue(0);
                ui.pbProgress->setMaximum(time);

                this->timer->start(1000);

                // ����ϵͳ״̬
                this->setStartupState(SysState::StateStaruping3);
            }
            else
            {
                // ��������
                this->onStartupFinished();
            }
        }
    }
    else
    {
        // ��������
        this->onStartupFinished();
    }
}

// ��������
void StartupWin::onStartupFinished()
{
    // ����ϵͳ״̬
    this->setStartupState(SysState::StateStartupFinished);

    // �����������
    this->switchToFuncWin(new CountWin());
}

// ���¿���״̬
void StartupWin::setStartupState(int state)
{
    // ����ϵͳ״̬
    SysState* sysState = Cache::sysState();
    if (sysState)
    {
        sysState->setStartupShutdownState(state);
    }
}