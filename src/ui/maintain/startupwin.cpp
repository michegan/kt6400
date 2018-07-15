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

    // 界面字符串
    this->setWindowText();

    // 窗口标识
    this->setWId("StartupWin");

    // 样本信息
    this->sampleInfo.sampleId = "BACKGROUND";

    this->sampleInfo.modes.workMode = WORK_MODE_BACKGROUND;
    this->sampleInfo.modes.analysisMode = ANALYSIS_MODE_CBC;
    this->sampleInfo.modes.bloodMode = BLOOD_MODE_BACKGROUND;

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(this->count, SIGNAL(algFinished()), this, SLOT(onCountAlgFinished()));
    connect(this->count, SIGNAL(countFinished(bool)), this, SLOT(onCountFinished(bool)));

    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));

    // 进入开机环节
    QTimer::singleShot(200, this, SLOT(onStartupTimeOut()));
}

StartupWin::~StartupWin()
{
    // 计数服务
    delete this->count;

    // 时序执行体
    delete this->timeseq;
}

// 界面字符串
void StartupWin::setWindowText()
{
    // 基类处理
    // FuncWin::setWindowText();

    // 子类处理
}

// 事件处理
void StartupWin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 绘制背景图
    const QImage* image = Resource::image("big_logo");
    if (image)
    {
        painter.drawImage(150, 0, *image);
    }

    // 基类处理
    FuncWin::paintEvent(event);
}

// 定时器超时
void StartupWin::onTimerOut()
{
    int value = ui.pbProgress->value();
    ui.pbProgress->setValue(value + 1);
}

void StartupWin::onStartupTimeOut()
{
    // 试剂检测


    // 更新系统状态
    this->setStartupState(SysState::StateStaruping0);


    // 启动液路初始化
    QString seqNo = SeqFile::initSeqNo();

    int ret = this->timeseq->runTimeseq(seqNo);
    if (EXIT_OK == ret)
    {
        // 开机提示
        this->setText(ui.lbNote, "IDS_LIQUID_INIT");

        // 开机进度
        float time = SeqFile::getSeqTime(seqNo);
        ui.pbProgress->setValue(0);
        ui.pbProgress->setMaximum(time);

        this->timer->start(1000);
    }
    else
    {
        // 开机结束
        this->onStartupFinished();
    }
}

// 算法结束
void StartupWin::onCountAlgFinished()
{
    do 
    {
        // 计数结果
        ParaList paraResult = this->count->paraResult();

        // 保存结果到数据库
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


        // 绑定参考范围
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

        // 本底范围检测
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

// 计数结束
void StartupWin::onCountFinished(bool result)
{
    // 开机结束
    this->onStartupFinished();
}

// 时序结束
void StartupWin::onTimeseqFinished(const QString& seqNo, bool result)
{
    // 停止定时器
    this->timer->stop();

    // 时序进度
    ui.pbProgress->setValue(ui.pbProgress->maximum());

    if (result)
    {
        // 液路初始化结束
        if (SeqFile::initSeqNo() == seqNo)
        {
            // 开机清洗
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

            // 启动开机清洗
            int ret = this->timeseq->runTimeseq(nextSeqNo);
            if (EXIT_OK == ret)
            {
                // 开机提示
                this->setText(ui.lbNote, "IDS_LIQUID_CLEANUP");

                // 开机进度
                float time = SeqFile::getSeqTime(seqNo);
                ui.pbProgress->setValue(0);
                ui.pbProgress->setMaximum(time);

                this->timer->start(1000);

                // 更新系统状态
                this->setStartupState(SysState::StateStaruping1);
            }
            else
            {
                // 开机结束
                this->onStartupFinished();
            }
        }
        // 开机清洗结束
        else if (SeqFile::startingUpSeqNo() == seqNo || SeqFile::wholeFillSeqNo() == seqNo)
        {
            // 更改关机类型
            ShutdownXml xml;
            if (xml.load())
            {
                xml.setTextValue2(KEY1_SHUTDOWN, KEY2_SHUTDOWN_TYPE, VALUE_SHUTDOWN_ABNORMAL);
                xml.save();
            }

            // 更新系统状态
            this->setStartupState(SysState::StateStaruping2);

            // 开机本底计数
            float time = 0;
            int ret = this->count->startCount(this->sampleInfo, &time);
            if (EXIT_OK == ret)
            {
                // 开机提示
                this->setText(ui.lbNote, "IDS_BACKGROUND_TEST");

                // 开机进度
                ui.pbProgress->setValue(0);
                ui.pbProgress->setMaximum(time);

                this->timer->start(1000);

                // 更新系统状态
                this->setStartupState(SysState::StateStaruping3);
            }
            else
            {
                // 开机结束
                this->onStartupFinished();
            }
        }
    }
    else
    {
        // 开机结束
        this->onStartupFinished();
    }
}

// 开机结束
void StartupWin::onStartupFinished()
{
    // 更新系统状态
    this->setStartupState(SysState::StateStartupFinished);

    // 进入计数界面
    this->switchToFuncWin(new CountWin());
}

// 更新开机状态
void StartupWin::setStartupState(int state)
{
    // 更新系统状态
    SysState* sysState = Cache::sysState();
    if (sysState)
    {
        sysState->setStartupShutdownState(state);
    }
}