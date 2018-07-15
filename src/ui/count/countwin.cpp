#include <QtDebug>
#include <QVariant>

#include "enum.h"
#include "cache.h"
#include "count.h"
#include "paras.h"
#include "print.h"
#include "seqfile.h"
#include "countwin.h"
#include "datetime.h"
#include "refrange.h"
#include "messagebox.h"
#include "refrangexml.h"
#include "maintaindialog.h"
#include "modeeditdialog.h"
#include "nextsampletable.h"
#include "adddiluentdialog.h"
#include "nextpeteditdialog.h"
#include "reviewsampletable.h"
#include "nextsampleeditdialog.h"


CountWin::CountWin(QWidget* parent)
    : CountFuncWin(parent), count(new Count()), progressDialog(new ProgressDialog(this)), addDiluentDialog(0), 
      sampleTable(ReviewSampleTable::instance()), countSampleInfo(new SampleInfo())
{
    ui.setupUi(this);

    // ���ڱ�ʶ
    this->setWId("CountWin");

    // ����״̬��
    this->createStatusBar();

    // �����ַ���
    this->setWindowText();

    // ��������ؼ�
    this->wbcParaWidget = new ParaWidget(this);
    this->wbcParaWidget->setParas(Paras::wbcReportParaNames());
    this->wbcParaWidget->setGeometry(5, 130, 260, 270);

    this->rbcParaWidget = new ParaWidget(this);
    this->rbcParaWidget->setParas(Paras::rbcReportParaNames());
    this->rbcParaWidget->setGeometry(270, 130, 260, 270);

    this->pltParaWidget = new ParaWidget(this);
    this->pltParaWidget->setParas(Paras::pltReportParaNames());
    this->pltParaWidget->setGeometry(535, 130, 260, 270);

    // ֱ��ͼ�ؼ�
    this->wbcHistWidget = new WbcHistWidget(this);
    this->wbcHistWidget->setGeometry(50, 405, 230, 150);

    this->rbcHistWidget = new RbcHistWidget(this);
    this->rbcHistWidget->setGeometry(285, 405, 230, 150);

    this->pltHistWidget = new PltHistWidget(this);
    this->pltHistWidget->setGeometry(520, 405, 230, 150);

    // ���ֳ����ͷǳ����
    bool isForPets = Cache::isForPets();
    ui.lbAge->setVisible(!isForPets);
    ui.leAge->setVisible(!isForPets);
    ui.lbSpecies->setVisible(isForPets);
    ui.leSpecies->setVisible(isForPets);

    // ��ǰ������Ϣ
    this->showCurrentSample();

    // ��һ������Ϣ
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();
    this->showNextSampleInfo(nextSampleInfo);

    // �����źŲ�
    connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    connect(ui.pbUnclog, SIGNAL(clicked()), this, SLOT(onBtnUnclogClicked()));
    connect(ui.pbAddDiluent, SIGNAL(clicked()), this, SLOT(onBtnAddDiluentClicked()));
    connect(ui.pbNextSample, SIGNAL(clicked()), this, SLOT(onBtnNextSampleClicked()));

    connect(ui.pbFirst, SIGNAL(clicked()), this, SLOT(onBtnFirstClicked()));
    connect(ui.pbLast, SIGNAL(clicked()), this, SLOT(onBtnLastClicked()));
    connect(ui.pbNext, SIGNAL(clicked()), this, SLOT(onBtnNextClicked()));
    connect(ui.pbPrevious, SIGNAL(clicked()), this, SLOT(onBtnPreviousClicked()));

    connect(this->count, SIGNAL(algFinished()), this, SLOT(onCountAlgFinished()));
    connect(this->count, SIGNAL(countFinished(bool)), this, SLOT(onCountFinished(bool)));
}

CountWin::~CountWin()
{
    // ��������
    delete this->count;

    // ����������Ϣ
    delete this->countSampleInfo;
}

// ����������
void CountWin::onAbsorbKeyDown()
{
    qDebug() << "CountWin onAbsorbKeyDown";

    // ���ִ��������Ǽ�ϡ��Һ������Ҳ�����Ǽ�������
    if (this->addDiluentDialog)
    {
        this->addDiluentDialog->onAbsorbKeyDown();
    }
    else
    {
        // ��һ������Ϣ
        SampleInfo nextSampleInfo = this->getNextSampleInfo();

        // ��������
        float countTime = 0;
        int ret = this->count->startCount(nextSampleInfo, &countTime);
        if (EXIT_OK == ret)
        {
            // �����ǰ������Ϣ
            this->clearWindow();

            // ����ʹ��
            this->enableWindow(false);
            // ������ʹ��
            this->enableAbsorbKey(false);

            // ������������Ϣ
            *this->countSampleInfo = nextSampleInfo;
            this->countSampleInfo->testTime = QDateTime::currentDateTime();

            this->showCurrentSampleInfo(*this->countSampleInfo);

            // �����µ���һ����
            nextSampleInfo.autoInc();
            this->setNextSampleInfo(nextSampleInfo);

            // ���ȶԻ���
            this->progressDialog->setText("Counting");
            this->progressDialog->exec(countTime);
        }
        else
        {
            // ��������ʱ��ʧ��
            this->onRunTimeseqFail(ret);
        }
    }
}

// �����ַ���
void CountWin::setWindowText()
{
    // ���ദ��
    CountFuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbPrint, "IDS_PRINT");
    this->setText(ui.pbUnclog, "IDS_UNCLOG");
    this->setText(ui.pbAddDiluent, "IDS_ADD_DILUENT");

    this->setText(ui.lbSampleId, "IDS_SAMPLE_ID");
    this->setText(ui.lbName, "IDS_NAME");
    this->setText(ui.lbGender, "IDS_GENDER");
    this->setText(ui.lbTestTime, "IDS_TEST_TIME");
    this->setText(ui.lbMode, "IDS_MODE");
    this->setText(ui.lbAge, "IDS_AGE");
    this->setText(ui.lbSpecies, "IDS_SPECIES");

    this->setText(this->lbNextSample, "IDS_NEXT_SAMPLE");
}

// ����״̬��
void CountWin::createStatusBar()
{
    // ���ദ��CountFuncWin���Ѿ����ù��������������Σ�
    // CountFuncWin::createStatusBar();

    // ���ദ��
    this->lbNextSample = new QLabel(this);
    this->lbNextSample->setGeometry(0, 565, 120, 32);

    this->lbNextSampleId = new QLabel(this);
    this->lbNextSampleId->setGeometry(120, 565, 200, 32);
}

// ����ʹ��
void CountWin::enableWindow(bool enable)
{
    // ���ദ��
    CountFuncWin::enableWindow(enable);

    // ���ദ��
    ui.pbLast->setEnabled(enable);
    ui.pbNext->setEnabled(enable);
    ui.pbFirst->setEnabled(enable);
    ui.pbPrint->setEnabled(enable);
    ui.pbUnclog->setEnabled(enable);
    ui.pbPrevious->setEnabled(enable);
    ui.pbAddDiluent->setEnabled(enable);
    ui.pbNextSample->setEnabled(enable);

    this->wbcHistWidget->setEnabled(enable);
    this->rbcHistWidget->setEnabled(enable);
    this->pltHistWidget->setEnabled(enable);

    this->lbNextSample->setEnabled(enable);
    this->lbNextSampleId->setEnabled(enable);
}

// ��ʾ��һ������Ϣ
void CountWin::showNextSampleInfo(const SampleInfo& sampleInfo)
{
    // ���ദ��
    CountFuncWin::showNextSampleInfo(sampleInfo);

    // ���ദ��
    this->lbNextSampleId->setText(sampleInfo.sampleId);
}

// ��ť���
void CountWin::onBtnPrintClicked()
{
    // ��ȡ������Ϣ
    QList<int> allSamples = this->sampleTable->allSamples();
    if (allSamples.isEmpty())
    {
        qWarning() << "";
    }
    else
    {
        // ��ǰ����
        int index = this->sampleTable->currentIndex();
        int fid = this->sampleTable->fid(index);

        // ��ȡ����
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // ��Ӧ�ο���Χ
            ParaList lowLimits;
            ParaList highLimits;
            if (RefRange::getLimits(sampleInfo, lowLimits, highLimits))
            {
                paraResult.setLimits(lowLimits, highLimits);
            }
            else
            {
                qWarning() << "CountWin showCurrentSample getLimits fail";
            }

            // ͼ�ν��
            HistInfo wbcHist;
            HistInfo rbcHist;
            HistInfo pltHist;

            if (!this->sampleTable->getSample(fid, wbcHist, rbcHist, pltHist))
            {
                qWarning() << "CountWin showCurrentSample getSample fail";
            }

            // ��ӡ����
            Print print;
            print.printSample(sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
        }
    }
}

void CountWin::onBtnUnclogClicked()
{
    MaintainDialog dialog(this);

    // �û���ʾ
    dialog.setText("Unclog");

    // ʱ��ţ����ݼ���������������
    int counts = 0;
    QString seqNo = (counts < 50 ? SeqFile::backFlushSeqNo() : SeqFile::enhancedFlushSeqNo());

    dialog.runTimeseq(seqNo);
}

void CountWin::onBtnAddDiluentClicked()
{
    // ������ϡ��Һ���ڶ���
    this->addDiluentDialog = new AddDiluentDialog(this);
    this->addDiluentDialog->exec();

    // ��ϡ��Һ���������ٸö����Ա�onAbsorbKeyDown����ʶ������
    this->addDiluentDialog->setParent(0);

    delete this->addDiluentDialog;
    this->addDiluentDialog = 0;
}

void CountWin::onBtnNextSampleClicked()
{
    // ��һ������Ϣ
    SampleInfo nextSampleInfo = this->getNextSampleInfo();

    // ��һ�����Ի���
    if (Cache::isForPets())
    {
        NextPetEditDialog dialog(this);
        dialog.setSampleInfo(nextSampleInfo);

        if (QDialog::Accepted == dialog.exec())
        {
            // �ӶԻ����ȡ������Ϣ
            nextSampleInfo = dialog.getSampleInfo();
            this->setNextSampleInfo(nextSampleInfo);
        }
        else
        {
            return;
        }
    }
    else
    {
        NextSampleEditDialog dialog(this);
        dialog.setSampleInfo(nextSampleInfo);

        if (QDialog::Accepted == dialog.exec())
        {
            // �ӶԻ����ȡ������Ϣ
            nextSampleInfo = dialog.getSampleInfo();
            this->setNextSampleInfo(nextSampleInfo);
        }
        else
        {
            return;
        }
    }
}

void CountWin::onBtnFirstClicked()
{
    // ���µ�ǰ����
    this->sampleTable->setCurrentIndex(0);

    // ��ʾ��ǰ����
    this->showCurrentSample();
}

void CountWin::onBtnLastClicked()
{
    // ���µ�ǰ����
    int index = this->sampleTable->allSamples().length();
    this->sampleTable->setCurrentIndex(index - 1);

    // ��ʾ��ǰ����
    this->showCurrentSample();
}

void CountWin::onBtnPreviousClicked()
{
    // ���µ�ǰ����
    int index = this->sampleTable->currentIndex();
    this->sampleTable->setCurrentIndex(index - 1);

    // ��ʾ��ǰ����
    this->showCurrentSample();
}

void CountWin::onBtnNextClicked()
{
    // ���µ�ǰ����
    int index = this->sampleTable->currentIndex();
    this->sampleTable->setCurrentIndex(index + 1);

    // ��ʾ��ǰ����
    this->showCurrentSample();
}

// �㷨����
void CountWin::onCountAlgFinished()
{
    // �����������ݿ�
    int fid = 0;
    if (this->sampleTable->addSample(fid, *this->countSampleInfo, this->count->paraResult()))
    {
        if (this->sampleTable->updateSample(fid, this->count->wbcHist(), this->count->rbcHist(), this->count->pltHist()))
        {
            // ��ʾ��ǰ����
            this->showCurrentSample();
        }
        else
        {
            qWarning() << "StartupWin onCountAlgFinished updateSample fail";
        }
    }
    else
    {
        qWarning() << "StartupWin onCountAlgFinished addSample fail";
    }
}

// ��������
void CountWin::onCountFinished(bool result)
{
    // ����ʹ��
    this->enableWindow(true);
    // ������ʹ��
    this->enableAbsorbKey(true);

    // ���²�ѯ�����⣬���һ��������Ϊ��ǰ����
    this->sampleTable->clearConditions();
    this->sampleTable->selectSamples();

    // �رս��ȶԻ���
    this->progressDialog->accept();
}

// �������
void CountWin::clearWindow()
{
    // ������Ϣ
    ui.leSampleId->clear();
    ui.leName->clear();
    ui.leAge->clear();
    ui.leMode->clear();
    ui.leGender->clear();
    ui.leTestTime->clear();
    ui.leSpecies->clear();

    // �������
    this->wbcParaWidget->clear();
    this->rbcParaWidget->clear();
    this->pltParaWidget->clear();

    // ͼ�ν��
    this->wbcHistWidget->clear();
    this->rbcHistWidget->clear();
    this->pltHistWidget->clear();
}

// ��ʾ��ǰ����
void CountWin::showCurrentSample()
{
    // �������
    this->clearWindow();

    // ��ʾ��ǰ����
    QList<int> allSamples = this->sampleTable->allSamples();
    if (allSamples.isEmpty())
    {
        // ���ܰ�ť
        ui.pbPrevious->setEnabled(false);
        ui.pbNext->setEnabled(false);
    }
    else
    {
        // ��ǰ����
        int index = this->sampleTable->currentIndex();
        int fid = this->sampleTable->fid(index);

        // ��ȡ����
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // ��Ӧ�ο���Χ
            ParaList lowLimits;
            ParaList highLimits;
            if (RefRange::getLimits(sampleInfo, lowLimits, highLimits))
            {
                paraResult.setLimits(lowLimits, highLimits);
            }
            else
            {
                qWarning() << "CountWin showCurrentSample getLimits fail";
            }

            // ������Ϣ
            this->showCurrentSampleInfo(sampleInfo);

            // �������
            this->wbcParaWidget->setParaList(paraResult);
            this->rbcParaWidget->setParaList(paraResult);
            this->pltParaWidget->setParaList(paraResult);
        }
        else
        {
            qWarning() << "CountWin showCurrentSample getSample sampleInfo paraResult fail";
        }

        // ͼ�ν��
        HistInfo wbcHist;
        HistInfo rbcHist;
        HistInfo pltHist;

        if (this->sampleTable->getSample(fid, wbcHist, rbcHist, pltHist))
        {
            this->wbcHistWidget->setHistInfo(wbcHist);
            this->rbcHistWidget->setHistInfo(rbcHist);
            this->pltHistWidget->setHistInfo(pltHist);
        }
        else
        {
            qWarning() << "CountWin showCurrentSample getSample histInfo fail";
        }

        // ���ܰ�ť
        ui.pbFirst->setEnabled(0 < index);
        ui.pbLast->setEnabled(index < allSamples.length() - 1);
        ui.pbPrevious->setEnabled(0 < index);
        ui.pbNext->setEnabled(index < allSamples.length() - 1);
    }
}

// ��ʾ����������Ϣ
void CountWin::showCurrentSampleInfo(const SampleInfo& sampleInfo)
{
    ui.leSampleId->setText(sampleInfo.sampleId);
    ui.leName->setText(sampleInfo.name);
    this->setText(ui.leGender, sampleInfo.genderIds());
    ui.leTestTime->setText(DateTime::datetimeToStringC(sampleInfo.testTime));
    this->setText(ui.leMode, sampleInfo.modes.ids());
    ui.leAge->setText(sampleInfo.age);

    QPixmap pixmap("./image/" + sampleInfo.modes.speciesImage());
    pixmap = pixmap.scaled(ui.leSpecies->height(), ui.leSpecies->height());
    ui.leSpecies->setPixmap(pixmap);
    ui.leSpecies->setWindowOpacity(0);
}