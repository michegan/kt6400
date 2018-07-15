#include <QTimer>

#include "enum.h"
#include "seqfile.h"
#include "asynctimeseq.h"
#include "adddiluentdialog.h"


AddDiluentDialog::AddDiluentDialog(QWidget* parent)
    : Dialog(parent), times(0), timer(new QTimer()), timeseq(new AsyncTimeseq())
{
    ui.setupUi(this);

    // ʱ��ţ���ϡ��Һ׼����
    this->prepareSeqNo = SeqFile::diluentInitSeqNo();
    // ʱ��ţ���ϡ��Һ��
    this->addDiluentSeqNo = SeqFile::diluentFloodSeqNo();
    // ʱ��ţ���ϡ��Һ��ϴ��
    this->cleanningSeqNo = SeqFile::cleanSeqNo();

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(ui.pbAddDiluent, SIGNAL(clicked()), this, SLOT(onBtnAddDiluentClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->timeseq, SIGNAL(timeseqFinished(const QString&, bool)), this, SLOT(onTimeseqFinished(const QString&, bool)));

    // ������ϡ��Һ׼��ʱ��
    QTimer::singleShot(200, this, SLOT(onPrepareTimerOut()));
}

AddDiluentDialog::~AddDiluentDialog()
{
    // ���ȶ�ʱ��
    delete this->timer;

    // ʱ��ִ����
    delete this->timeseq;
}

// ����������
void AddDiluentDialog::onAbsorbKeyDown()
{
    this->onBtnAddDiluentClicked();
}

// ��ʱ����ʱ
void AddDiluentDialog::onTimerOut()
{
    int value = ui.pbProgress->value();
    ui.pbProgress->setValue(value + 1);
}

void AddDiluentDialog::onPrepareTimerOut()
{
    // ����ʱ��
    QString seqNo = this->prepareSeqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // ʹ�ܽ���
        this->enableWindow(false);

        // ��ϡ��Һ׼����
        ui.lbNotification->setText("Preparing for add diluent");

        // ʱ�����
        float time = SeqFile::getSeqTime(seqNo);
        ui.pbProgress->setValue(0);
        ui.pbProgress->setMaximum(time);

        this->timer->start(1000);
    }
}

// ��ť���
void AddDiluentDialog::onBtnAddDiluentClicked()
{
    // ����ʱ��
    QString seqNo = this->addDiluentSeqNo;
    if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
    {
        // ʹ�ܽ���
        this->enableWindow(false);

        // ��ϡ��Һ������
        this->times ++;
        ui.pbAddDiluent->setText(QString("Add Diluent (%1)").arg(this->times));

        // ʱ�����
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
        // ����ʱ��
        QString seqNo = this->cleanningSeqNo;
        if (EXIT_OK == this->timeseq->runTimeseq(seqNo))
        {
            // ʹ�ܽ���
            this->enableWindow(false);

            // ��ϡ��Һ��ϴ��
            ui.lbNotification->setText("System cleannig");

            // ʱ�����
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

// ʱ�����
void AddDiluentDialog::onTimeseqFinished(const QString& seqNo, bool result)
{
    // ֹͣ��ʱ��
    this->timer->stop();

    // ʱ�����
    ui.pbProgress->setValue(ui.pbProgress->maximum());

    // ����ʹ��
    this->enableWindow(true);

    // ������ʾ
    if (this->prepareSeqNo == seqNo || this->addDiluentSeqNo == seqNo)
    {
        ui.lbNotification->setText("Press Absorbkey to add diluent");
    }
    else if (this->cleanningSeqNo == seqNo)
    {
        this->reject();
    }
}

// ʹ�ܽ���
void AddDiluentDialog::enableWindow(bool enable)
{
    ui.pbCancel->setEnabled(enable);
    ui.pbAddDiluent->setEnabled(enable);
}