#include <QFile>

#include "dma.h"
#include "newalg.h"
#include "pulsewin.h"


// 每页粒子数
#define ONE_PAGE_PULSES     (1000)


PulseWin::PulseWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // 创建状态条
    this->createStatusBar();

    // 窗口标识
    this->setWId("PulseWin");

    // 数据信息
    this->wbcDatas = 0;
    this->rbcDatas = 0;
    this->pltDatas = 0;

    this->wbcDataLen = 0;
    this->rbcDataLen = 0;
    this->pltDataLen = 0;

    // 脉冲图形
    this->wbcPulse = new PulseWidget(this);
    this->wbcPulse->setYAxis(0, 255, 50);
    this->wbcPulse->setGeometry(10, 100, 780, 150);

    this->rbcPulse = new PulseWidget(this);
    this->rbcPulse->setYAxis(0, 255, 50);
    this->rbcPulse->setGeometry(10, 255, 780, 150);

    this->pltPulse = new PulseWidget(this);
    this->pltPulse->setYAxis(0, 255, 50);
    this->pltPulse->setGeometry(10, 410, 780, 150);

    // 滚动定时器
    this->timer = new QTimer();

#ifdef _WIN32
    // 默认从FILE读取数据
    ui.rbFromFile->setChecked(true);
    this->onCheckBoxFromFileToggled(true);
#else
    // 默认从BUFFER读取数据
    ui.rbFromBuffer->setChecked(true);
    this->onCheckBoxFromBufferToggled(true);
#endif

    // 屏蔽部分功能
    ui.pbAlg->setVisible(false);
    ui.rbFromFile->setVisible(false);
    ui.rbFromBuffer->setVisible(false);

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(ui.pbAlg, SIGNAL(clicked()), this, SLOT(onBtnAlgClicked()));

    connect(ui.pbPageFirst, SIGNAL(clicked()), this, SLOT(onBtnPageFirstClicked()));
    connect(ui.pbPageGoto, SIGNAL(clicked()), this, SLOT(onBtnPageGotoClicked()));
    connect(ui.pbPageLast, SIGNAL(clicked()), this, SLOT(onBtnPageLastClicked()));

    connect(ui.pbScrollDown, SIGNAL(clicked()), this, SLOT(onBtnScrollDownClicked()));
    connect(ui.pbScrollUp, SIGNAL(clicked()), this, SLOT(onBtnScrollUpClicked()));
    connect(ui.pbScrollStop, SIGNAL(clicked()), this, SLOT(onBtnScrollStopClicked()));

    connect(ui.rbFromFile, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxFromFileToggled(bool)));
    connect(ui.rbFromBuffer, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxFromBufferToggled(bool)));
}

PulseWin::~PulseWin()
{
    // 滚动定时器
    delete this->timer;

    // 数据信息
    if (this->wbcDatas)
    {
        delete [] this->wbcDatas;
    }
    if (this->rbcDatas)
    {
        delete [] this->rbcDatas;
    }
    if (this->pltDatas)
    {
        delete [] this->pltDatas;
    }
}

// 创建状态条
void PulseWin::createStatusBar()
{
    // 基类处理
    FuncWin::createStatusBar();

    // 子类处理
    this->lbPos = new QLabel(this);
    this->lbPos->setGeometry(0, 565, 240, 30);
}

// 定时器超时
void PulseWin::onTimerOut()
{
    if (this->direction < 0)
    {
        if (0 < this->currentPage)
        {
            // 上一页
            this->currentPage --;

            // 显示当前页
            this->showCurrentPage();
        }
        else
        {
            // 停止滚动
            this->onBtnScrollStopClicked();
        }
    }
    else if (0 < this->direction)
    {
        if (this->currentPage < this->numOfPages - 1)
        {
            // 下一页
            this->currentPage ++;

            // 显示当前页
            this->showCurrentPage();
        }
        else
        {
            // 停止滚动
            this->onBtnScrollStopClicked();
        }
    }
}

// 按钮点击
void PulseWin::onBtnAlgClicked()
{
    Alg::init();
}

void PulseWin::onBtnPageFirstClicked()
{
    // 首页
    this->currentPage = 0;

    // 显示当前页
    this->showCurrentPage();
}

void PulseWin::onBtnPageGotoClicked()
{
    QString text = ui.lePage->text();
    
    bool ok = false;
    int page = text.toInt(&ok);

    if (ok)
    {
        if (0 <= page && page < this->numOfPages)
        {
            this->currentPage = page;

            // 显示当前页
            this->showCurrentPage();
        }
    }
}

void PulseWin::onBtnPageLastClicked()
{
    // 下一页
    if (0 < this->numOfPages)
    {
        this->currentPage = this->numOfPages - 1;
    }

    // 显示当前页
    this->showCurrentPage();
}

void PulseWin::onBtnScrollDownClicked()
{
    this->direction = -1;
    this->timer->start(300);
}

void PulseWin::onBtnScrollUpClicked()
{
    this->direction = 1;
    this->timer->start(300);
}

void PulseWin::onBtnScrollStopClicked()
{
    this->direction = 0;
    this->timer->stop();
}

void PulseWin::onCheckBoxFromFileToggled(bool checked)
{
    // 停止定时器
    this->timer->stop();
    // 滚动方向未知
    this->direction = 0;

    // WBC数据信息
    {
        // 释放内存
        if (this->wbcDatas)
        {
            delete [] this->wbcDatas;
        }

        // 加载脉冲数据
        QFile file("./wbc.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->wbcDataLen = file.size();
            this->wbcDatas = new char[this->wbcDataLen];

            file.read(this->wbcDatas, this->wbcDataLen);
        }

        file.close();
    }

    // RBC数据信息
    {
        // 释放内存
        if (this->rbcDatas)
        {
            delete [] this->rbcDatas;
        }

        // 加载脉冲数据
        QFile file("./rbc.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->rbcDataLen = file.size();
            this->rbcDatas = new char[this->rbcDataLen];

            file.read(this->rbcDatas, this->rbcDataLen);
        }

        file.close();
    }

    // PLT数据信息
    {
        // 释放内存
        if (this->pltDatas)
        {
            delete [] this->pltDatas;
        }

        // 加载脉冲数据
        QFile file("./plt.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->pltDataLen = file.size();
            this->pltDatas = new char[this->pltDataLen];

            file.read(this->pltDatas, this->pltDataLen);
        }

        file.close();
    }

    // 页数信息
    int maxDataLen = qMax<int>(this->wbcDataLen, this->rbcDataLen);
    maxDataLen = qMax<int>(maxDataLen, this->pltDataLen);

    this->numOfPages = (maxDataLen / ONE_PAGE_PULSES + 1);

    // 显示第一页
    this->onBtnPageFirstClicked();
}

void PulseWin::onCheckBoxFromBufferToggled(bool checked)
{
    // 停止定时器
    this->timer->stop();
    // 滚动方向未知
    this->direction = 0;

    // WBC数据信息
    {
        // 释放内存
        if (this->wbcDatas)
        {
            delete [] this->wbcDatas;
        }

        // 加载脉冲数据
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->wbcDataLen = dmaBuf->wbcSamplingBufLen;
            this->wbcDatas = new char[this->wbcDataLen];

            memcpy(this->wbcDatas, (char*)dmaBuf->pWbcSamplingBuf, this->wbcDataLen);
        }
    }

    // RBC数据信息
    {
        // 释放内存
        if (this->rbcDatas)
        {
            delete [] this->rbcDatas;
        }

        // 加载脉冲数据
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->rbcDataLen = dmaBuf->rbcSamplingBufLen;
            this->rbcDatas = new char[this->rbcDataLen];

            memcpy(this->rbcDatas, (char*)dmaBuf->pRbcSamplingBuf, this->rbcDataLen);
        }
    }

    // PLT数据信息
    {
        // 释放内存
        if (this->pltDatas)
        {
            delete [] this->pltDatas;
        }

        // 加载脉冲数据
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->pltDataLen = dmaBuf->pltSamplingBufLen;
            this->pltDatas = new char[this->pltDataLen];

            memcpy(this->pltDatas, (char*)dmaBuf->pPltSamplingBuf, this->pltDataLen);
        }
    }

    // 页数信息
    int maxDataLen = qMax<int>(this->wbcDataLen, this->rbcDataLen);
    maxDataLen = qMax<int>(maxDataLen, this->pltDataLen);

    this->numOfPages = (maxDataLen / ONE_PAGE_PULSES + 1);

    // 显示第一页
    this->onBtnPageFirstClicked();
}

// 显示当前页
void PulseWin::showCurrentPage()
{
    // WBC脉冲图形
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->wbcDataLen - offset);

        this->wbcPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->wbcPulse->setData<unsigned char>((unsigned char*)this->wbcDatas + offset, dataLen);
    }

    // RBC脉冲图形
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->rbcDataLen - offset);

        this->rbcPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->rbcPulse->setData<unsigned char>((unsigned char*)this->rbcDatas + offset, dataLen);
    }

    // PLT脉冲图形
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->pltDataLen - offset);

        this->pltPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->pltPulse->setData<unsigned char>((unsigned char*)this->pltDatas + offset, dataLen);
    }

    // 当前页
    this->lbPos->setText(QString("Page : %1 / %2").arg(this->currentPage).arg(this->numOfPages));
}