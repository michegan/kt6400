#include <QTimer>

#include "enum.h"
#include "seqfile.h"
#include "asynctimeseq.h"
#include "adddiluentdialog.h"


AddDiluentDialog::AddDiluentDialog(QWidget* parent)
    : Dialog(parent), times(0), timer(new QTimer()), timeseq(new AsyncTimeseq())
{
    ui.setupUi(this);

    // 时序号（加稀释液准备）
    this->prepareSeqNo = SeqFile::diluentInitSeqNo();
    // 时序号（加稀释液）
    this->addDiluentSeqNo = SeqFile::diluentFloodSeqNo();
    // 时序号（加稀释液清洗）
    this->cleanningSeqNo = SeqFile::cleanSeqNo();

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(ui.pbAddDiluent, SIGNAL(clicked()), this, SLOT(onBtnAddDiluentClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));

    // 启动加稀释液准备时序
    QTimer::singleShot(200, this, SLOT(onPrepareTimerOut()));
}

AddDiluentDialog::~AddDiluentDialog()
{
    // 进度定时器
    delete this->timer;

    // 时序执行体
    delete this->timeseq;
}

// 吸样键按下
void AddDiluentDialog::onAbsorbKeyDown()
{
    this->onBtnAddDiluentClicked();
}

// 定时器超时
void AddDiluentDialog::onTimerOut()
{
    int value = ui.pbProgress->value();
    ui.pbProgress->setValue(value + 1);
}

void AddDiluentDialog::onPrepareTimerOut()
{
    // 启动时序
    QString seqNo = this->prepareSeqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // 使能界面
        this->enableWindow(false);

        // 加稀释液准备中
        ui.lbNotification->setText("Preparing for add diluent");

        // 时序进度
        float time = SeqFile::getSeqTime(seqNo);
        ui.pbProgress->setValue(0);
        ui.pbProgress->setMaximum(time);

        this->timer->start(1000);
    }
}

// 按钮点击
void AddDiluentDialog::onBtnAddDiluentClicked()
{
    // 启动时序
    QString seqNo = this->addDiluentSeqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // 使能界面
        this->enableWindow(false);

        // 加稀释液进行中
        this->times ++;
        ui.pbAddDiluent->setText(QString("Add Diluent (%1)").arg(this->times));

        // 时序进度
        float time = SeqFile::getSeqTime(seqNo);
        ui.pbProgress->setValue(0);
        ui.pbProgress->setMaximum(time);

        this->timer->start(1000);
    }
}

void AddDiluentDialog::onBtnCancelClicked()
{
    if (0 < this->times)
    {
        // 启动时序
        QString seqNo = this->cleanningSeqNo;
        if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
        {
            // 使能界面
            this->enableWindow(false);

            // 加稀释液清洗中
            ui.lbNotification->setText("System cleannig");

            // 时序进度
            float time = SeqFile::getSeqTime(seqNo);
            ui.pbProgress->setValue(0);
            ui.pbProgress->setMaximum(time);

            this->timer->start(1000);
        }
    }
    else
    {
        this->reject();
    }
}

// 时序结束
void AddDiluentDialog::onTimeseqFinished(const QString& seqNo, bool result)
{
    // 停止定时器
    this->timer->stop();

    // 时序进度
    ui.pbProgress->setValue(ui.pbProgress->maximum());

    // 界面使能
    this->enableWindow(true);

    // 界面提示
    if (this->prepareSeqNo == seqNo || this->addDiluentSeqNo == seqNo)
    {
        ui.lbNotification->setText("Press Absorbkey to add diluent");
    }
    else if (this->cleanningSeqNo == seqNo)
    {
        this->reject();
    }
}

// 使能界面
void AddDiluentDialog::enableWindow(bool enable)
{
    ui.pbCancel->setEnabled(enable);
    ui.pbAddDiluent->setEnabled(enable);
}