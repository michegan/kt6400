#include "timeseq.h"
#include "sensordialog.h"


SensorDialog::SensorDialog(QWidget* parent)
    : Dialog(parent), timer(new QTimer(this))
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ������ʱ��
    this->timer->start(3 * 1000);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

SensorDialog::~SensorDialog()
{

}

// �����ַ���
void SensorDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.leLyse, "IDS_LYSE");
    this->setText(ui.leDiluent, "IDS_DILUENT");
    this->setText(ui.leWaste, "IDS_WASTE");

    this->setText(ui.pbOk, "IDS_OK");
}

// ��ʱ����ʱ
void SensorDialog::onTimerOut()
{
    bool hasLyse = Timeseq::hasLyse();
    this->setText(ui.leLyse, (hasLyse ? "IDS_YES" : "IDS_NO"));

    bool hasDiluent = Timeseq::hasDiluent();
    this->setText(ui.leDiluent, (hasDiluent ? "IDS_YES" : "IDS_NO"));

    bool wasteFull = Timeseq::isWasteFull();
    this->setText(ui.leWaste, (wasteFull ? "IDS_YES" : "IDS_NO"));
}