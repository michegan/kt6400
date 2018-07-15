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

    // 窗口标识
    this->setWId("CountWin");

    // 创建状态条
    this->createStatusBar();

    // 界面字符串
    this->setWindowText();

    // 参数结果控件
    this->wbcParaWidget = new ParaWidget(this);
    this->wbcParaWidget->setParas(Paras::wbcReportParaNames());
    this->wbcParaWidget->setGeometry(5, 130, 260, 270);

    this->rbcParaWidget = new ParaWidget(this);
    this->rbcParaWidget->setParas(Paras::rbcReportParaNames());
    this->rbcParaWidget->setGeometry(270, 130, 260, 270);

    this->pltParaWidget = new ParaWidget(this);
    this->pltParaWidget->setParas(Paras::pltReportParaNames());
    this->pltParaWidget->setGeometry(535, 130, 260, 270);

    // 直方图控件
    this->wbcHistWidget = new WbcHistWidget(this);
    this->wbcHistWidget->setGeometry(50, 405, 230, 150);

    this->rbcHistWidget = new RbcHistWidget(this);
    this->rbcHistWidget->setGeometry(285, 405, 230, 150);

    this->pltHistWidget = new PltHistWidget(this);
    this->pltHistWidget->setGeometry(520, 405, 230, 150);

    // 区分宠物版和非宠物版
    bool isForPets = Cache::isForPets();
    ui.lbAge->setVisible(!isForPets);
    ui.leAge->setVisible(!isForPets);
    ui.lbSpecies->setVisible(isForPets);
    ui.leSpecies->setVisible(isForPets);

    // 当前样本信息
    this->showCurrentSample();

    // 下一样本信息
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();
    this->showNextSampleInfo(nextSampleInfo);

    // 关联信号槽
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
    // 计数服务
    delete this->count;

    // 计数样本信息
    delete this->countSampleInfo;
}

// 吸样键按下
void CountWin::onAbsorbKeyDown()
{
    qDebug() << "CountWin onAbsorbKeyDown";

    // 区分处理，可能是加稀释液操作，也可能是计数操作
    if (this->addDiluentDialog)
    {
        this->addDiluentDialog->onAbsorbKeyDown();
    }
    else
    {
        // 下一样本信息
        SampleInfo nextSampleInfo = this->getNextSampleInfo();

        // 启动计数
        float countTime = 0;
        int ret = this->count->startCount(nextSampleInfo, &countTime);
        if (EXIT_OK == ret)
        {
            // 清除当前样本信息
            this->clearWindow();

            // 界面使能
            this->enableWindow(false);
            // 吸样键使能
            this->enableAbsorbKey(false);

            // 计数中样本信息
            *this->countSampleInfo = nextSampleInfo;
            this->countSampleInfo->testTime = QDateTime::currentDateTime();

            this->showCurrentSampleInfo(*this->countSampleInfo);

            // 计算新的下一样本
            nextSampleInfo.autoInc();
            this->setNextSampleInfo(nextSampleInfo);

            // 进度对话框
            this->progressDialog->setText("Counting");
            this->progressDialog->exec(countTime);
        }
        else
        {
            // 启动计数时序失败
            this->onRunTimeseqFail(ret);
        }
    }
}

// 界面字符串
void CountWin::setWindowText()
{
    // 基类处理
    CountFuncWin::setWindowText();

    // 子类处理
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

// 创建状态条
void CountWin::createStatusBar()
{
    // 基类处理（CountFuncWin中已经调用过，所以这里屏蔽）
    // CountFuncWin::createStatusBar();

    // 子类处理
    this->lbNextSample = new QLabel(this);
    this->lbNextSample->setGeometry(0, 565, 120, 32);

    this->lbNextSampleId = new QLabel(this);
    this->lbNextSampleId->setGeometry(120, 565, 200, 32);
}

// 界面使能
void CountWin::enableWindow(bool enable)
{
    // 基类处理
    CountFuncWin::enableWindow(enable);

    // 子类处理
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

// 显示下一样本信息
void CountWin::showNextSampleInfo(const SampleInfo& sampleInfo)
{
    // 基类处理
    CountFuncWin::showNextSampleInfo(sampleInfo);

    // 子类处理
    this->lbNextSampleId->setText(sampleInfo.sampleId);
}

// 按钮点击
void CountWin::onBtnPrintClicked()
{
    // 获取样本信息
    QList<int> allSamples = this->sampleTable->allSamples();
    if (allSamples.isEmpty())
    {
        qWarning() << "";
    }
    else
    {
        // 当前样本
        int index = this->sampleTable->currentIndex();
        int fid = this->sampleTable->fid(index);

        // 获取样本
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // 对应参考范围
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

            // 图形结果
            HistInfo wbcHist;
            HistInfo rbcHist;
            HistInfo pltHist;

            if (!this->sampleTable->getSample(fid, wbcHist, rbcHist, pltHist))
            {
                qWarning() << "CountWin showCurrentSample getSample fail";
            }

            // 打印样本
            Print print;
            print.printSample(sampleInfo, paraResult, wbcHist, rbcHist, pltHist);
        }
    }
}

void CountWin::onBtnUnclogClicked()
{
    MaintainDialog dialog(this);

    // 用户提示
    dialog.setText("Unclog");

    // 时序号（根据计数次数来决定）
    int counts = 0;
    QString seqNo = (counts < 50 ? SeqFile::backFlushSeqNo() : SeqFile::enhancedFlushSeqNo());

    dialog.runTimeseq(seqNo);
}

void CountWin::onBtnAddDiluentClicked()
{
    // 创建加稀释液窗口对象
    this->addDiluentDialog = new AddDiluentDialog(this);
    this->addDiluentDialog->exec();

    // 加稀释液结束后，销毁该对象，以便onAbsorbKeyDown进行识别区分
    this->addDiluentDialog->setParent(0);

    delete this->addDiluentDialog;
    this->addDiluentDialog = 0;
}

void CountWin::onBtnNextSampleClicked()
{
    // 下一样本信息
    SampleInfo nextSampleInfo = this->getNextSampleInfo();

    // 下一样本对话框
    if (Cache::isForPets())
    {
        NextPetEditDialog dialog(this);
        dialog.setSampleInfo(nextSampleInfo);

        if (QDialog::Accepted == dialog.exec())
        {
            // 从对话框获取样本信息
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
            // 从对话框获取样本信息
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
    // 更新当前样本
    this->sampleTable->setCurrentIndex(0);

    // 显示当前样本
    this->showCurrentSample();
}

void CountWin::onBtnLastClicked()
{
    // 更新当前样本
    int index = this->sampleTable->allSamples().length();
    this->sampleTable->setCurrentIndex(index - 1);

    // 显示当前样本
    this->showCurrentSample();
}

void CountWin::onBtnPreviousClicked()
{
    // 更新当前样本
    int index = this->sampleTable->currentIndex();
    this->sampleTable->setCurrentIndex(index - 1);

    // 显示当前样本
    this->showCurrentSample();
}

void CountWin::onBtnNextClicked()
{
    // 更新当前样本
    int index = this->sampleTable->currentIndex();
    this->sampleTable->setCurrentIndex(index + 1);

    // 显示当前样本
    this->showCurrentSample();
}

// 算法结束
void CountWin::onCountAlgFinished()
{
    // 保存结果到数据库
    int fid = 0;
    if (this->sampleTable->addSample(fid, *this->countSampleInfo, this->count->paraResult()))
    {
        if (this->sampleTable->updateSample(fid, this->count->wbcHist(), this->count->rbcHist(), this->count->pltHist()))
        {
            // 显示当前样本
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

// 计数结束
void CountWin::onCountFinished(bool result)
{
    // 界面使能
    this->enableWindow(true);
    // 吸样键使能
    this->enableAbsorbKey(true);

    // 重新查询样本库，最后一个样本作为当前样本
    this->sampleTable->clearConditions();
    this->sampleTable->selectSamples();

    // 关闭进度对话框
    this->progressDialog->accept();
}

// 界面清空
void CountWin::clearWindow()
{
    // 样本信息
    ui.leSampleId->clear();
    ui.leName->clear();
    ui.leAge->clear();
    ui.leMode->clear();
    ui.leGender->clear();
    ui.leTestTime->clear();
    ui.leSpecies->clear();

    // 参数结果
    this->wbcParaWidget->clear();
    this->rbcParaWidget->clear();
    this->pltParaWidget->clear();

    // 图形结果
    this->wbcHistWidget->clear();
    this->rbcHistWidget->clear();
    this->pltHistWidget->clear();
}

// 显示当前样本
void CountWin::showCurrentSample()
{
    // 界面清空
    this->clearWindow();

    // 显示当前样本
    QList<int> allSamples = this->sampleTable->allSamples();
    if (allSamples.isEmpty())
    {
        // 功能按钮
        ui.pbPrevious->setEnabled(false);
        ui.pbNext->setEnabled(false);
    }
    else
    {
        // 当前样本
        int index = this->sampleTable->currentIndex();
        int fid = this->sampleTable->fid(index);

        // 获取样本
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // 对应参考范围
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

            // 样本信息
            this->showCurrentSampleInfo(sampleInfo);

            // 参数结果
            this->wbcParaWidget->setParaList(paraResult);
            this->rbcParaWidget->setParaList(paraResult);
            this->pltParaWidget->setParaList(paraResult);
        }
        else
        {
            qWarning() << "CountWin showCurrentSample getSample sampleInfo paraResult fail";
        }

        // 图形结果
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

        // 功能按钮
        ui.pbFirst->setEnabled(0 < index);
        ui.pbLast->setEnabled(index < allSamples.length() - 1);
        ui.pbPrevious->setEnabled(0 < index);
        ui.pbNext->setEnabled(index < allSamples.length() - 1);
    }
}

// 显示计数样本信息
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