#include <QFile>

#include "dma.h"
#include "newalg.h"
#include "pulsewin.h"


// ÿҳ������
#define ONE_PAGE_PULSES     (1000)


PulseWin::PulseWin(QWidget* parent)
    : FuncWin(parent)
{
    ui.setupUi(this);

    // ����״̬��
    this->createStatusBar();

    // ���ڱ�ʶ
    this->setWId("PulseWin");

    // ������Ϣ
    this->wbcDatas = 0;
    this->rbcDatas = 0;
    this->pltDatas = 0;

    this->wbcDataLen = 0;
    this->rbcDataLen = 0;
    this->pltDataLen = 0;

    // ����ͼ��
    this->wbcPulse = new PulseWidget(this);
    this->wbcPulse->setYAxis(0, 255, 50);
    this->wbcPulse->setGeometry(10, 100, 780, 150);

    this->rbcPulse = new PulseWidget(this);
    this->rbcPulse->setYAxis(0, 255, 50);
    this->rbcPulse->setGeometry(10, 255, 780, 150);

    this->pltPulse = new PulseWidget(this);
    this->pltPulse->setYAxis(0, 255, 50);
    this->pltPulse->setGeometry(10, 410, 780, 150);

    // ������ʱ��
    this->timer = new QTimer();

#ifdef _WIN32
    // Ĭ�ϴ�FILE��ȡ����
    ui.rbFromFile->setChecked(true);
    this->onCheckBoxFromFileToggled(true);
#else
    // Ĭ�ϴ�BUFFER��ȡ����
    ui.rbFromBuffer->setChecked(true);
    this->onCheckBoxFromBufferToggled(true);
#endif

    // ���β��ֹ���
    ui.pbAlg->setVisible(false);
    ui.rbFromFile->setVisible(false);
    ui.rbFromBuffer->setVisible(false);

    // �����źŲ�
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
    // ������ʱ��
    delete this->timer;

    // ������Ϣ
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

// ����״̬��
void PulseWin::createStatusBar()
{
    // ���ദ��
    FuncWin::createStatusBar();

    // ���ദ��
    this->lbPos = new QLabel(this);
    this->lbPos->setGeometry(0, 565, 240, 30);
}

// ��ʱ����ʱ
void PulseWin::onTimerOut()
{
    if (this->direction < 0)
    {
        if (0 < this->currentPage)
        {
            // ��һҳ
            this->currentPage --;

            // ��ʾ��ǰҳ
            this->showCurrentPage();
        }
        else
        {
            // ֹͣ����
            this->onBtnScrollStopClicked();
        }
    }
    else if (0 < this->direction)
    {
        if (this->currentPage < this->numOfPages - 1)
        {
            // ��һҳ
            this->currentPage ++;

            // ��ʾ��ǰҳ
            this->showCurrentPage();
        }
        else
        {
            // ֹͣ����
            this->onBtnScrollStopClicked();
        }
    }
}

// ��ť���
void PulseWin::onBtnAlgClicked()
{
    Alg::init();
}

void PulseWin::onBtnPageFirstClicked()
{
    // ��ҳ
    this->currentPage = 0;

    // ��ʾ��ǰҳ
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

            // ��ʾ��ǰҳ
            this->showCurrentPage();
        }
    }
}

void PulseWin::onBtnPageLastClicked()
{
    // ��һҳ
    if (0 < this->numOfPages)
    {
        this->currentPage = this->numOfPages - 1;
    }

    // ��ʾ��ǰҳ
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
    // ֹͣ��ʱ��
    this->timer->stop();
    // ��������δ֪
    this->direction = 0;

    // WBC������Ϣ
    {
        // �ͷ��ڴ�
        if (this->wbcDatas)
        {
            delete [] this->wbcDatas;
        }

        // ������������
        QFile file("./wbc.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->wbcDataLen = file.size();
            this->wbcDatas = new char[this->wbcDataLen];

            file.read(this->wbcDatas, this->wbcDataLen);
        }

        file.close();
    }

    // RBC������Ϣ
    {
        // �ͷ��ڴ�
        if (this->rbcDatas)
        {
            delete [] this->rbcDatas;
        }

        // ������������
        QFile file("./rbc.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->rbcDataLen = file.size();
            this->rbcDatas = new char[this->rbcDataLen];

            file.read(this->rbcDatas, this->rbcDataLen);
        }

        file.close();
    }

    // PLT������Ϣ
    {
        // �ͷ��ڴ�
        if (this->pltDatas)
        {
            delete [] this->pltDatas;
        }

        // ������������
        QFile file("./plt.org");
        if (file.open(QIODevice::ReadWrite))
        {
            this->pltDataLen = file.size();
            this->pltDatas = new char[this->pltDataLen];

            file.read(this->pltDatas, this->pltDataLen);
        }

        file.close();
    }

    // ҳ����Ϣ
    int maxDataLen = qMax<int>(this->wbcDataLen, this->rbcDataLen);
    maxDataLen = qMax<int>(maxDataLen, this->pltDataLen);

    this->numOfPages = (maxDataLen / ONE_PAGE_PULSES + 1);

    // ��ʾ��һҳ
    this->onBtnPageFirstClicked();
}

void PulseWin::onCheckBoxFromBufferToggled(bool checked)
{
    // ֹͣ��ʱ��
    this->timer->stop();
    // ��������δ֪
    this->direction = 0;

    // WBC������Ϣ
    {
        // �ͷ��ڴ�
        if (this->wbcDatas)
        {
            delete [] this->wbcDatas;
        }

        // ������������
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->wbcDataLen = dmaBuf->wbcSamplingBufLen;
            this->wbcDatas = new char[this->wbcDataLen];

            memcpy(this->wbcDatas, (char*)dmaBuf->pWbcSamplingBuf, this->wbcDataLen);
        }
    }

    // RBC������Ϣ
    {
        // �ͷ��ڴ�
        if (this->rbcDatas)
        {
            delete [] this->rbcDatas;
        }

        // ������������
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->rbcDataLen = dmaBuf->rbcSamplingBufLen;
            this->rbcDatas = new char[this->rbcDataLen];

            memcpy(this->rbcDatas, (char*)dmaBuf->pRbcSamplingBuf, this->rbcDataLen);
        }
    }

    // PLT������Ϣ
    {
        // �ͷ��ڴ�
        if (this->pltDatas)
        {
            delete [] this->pltDatas;
        }

        // ������������
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            this->pltDataLen = dmaBuf->pltSamplingBufLen;
            this->pltDatas = new char[this->pltDataLen];

            memcpy(this->pltDatas, (char*)dmaBuf->pPltSamplingBuf, this->pltDataLen);
        }
    }

    // ҳ����Ϣ
    int maxDataLen = qMax<int>(this->wbcDataLen, this->rbcDataLen);
    maxDataLen = qMax<int>(maxDataLen, this->pltDataLen);

    this->numOfPages = (maxDataLen / ONE_PAGE_PULSES + 1);

    // ��ʾ��һҳ
    this->onBtnPageFirstClicked();
}

// ��ʾ��ǰҳ
void PulseWin::showCurrentPage()
{
    // WBC����ͼ��
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->wbcDataLen - offset);

        this->wbcPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->wbcPulse->setData<unsigned char>((unsigned char*)this->wbcDatas + offset, dataLen);
    }

    // RBC����ͼ��
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->rbcDataLen - offset);

        this->rbcPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->rbcPulse->setData<unsigned char>((unsigned char*)this->rbcDatas + offset, dataLen);
    }

    // PLT����ͼ��
    {
        int offset = this->currentPage * ONE_PAGE_PULSES;
        int dataLen = qMin<int>(ONE_PAGE_PULSES, this->pltDataLen - offset);

        this->pltPulse->setXAxis(offset, offset + ONE_PAGE_PULSES, ONE_PAGE_PULSES / 10);
        this->pltPulse->setData<unsigned char>((unsigned char*)this->pltDatas + offset, dataLen);
    }

    // ��ǰҳ
    this->lbPos->setText(QString("Page : %1 / %2").arg(this->currentPage).arg(this->numOfPages));
}