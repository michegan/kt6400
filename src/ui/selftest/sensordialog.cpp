#include "timeseq.h"
#include "sensordialog.h"


SensorDialog::SensorDialog(QWidget* parent)
    : Dialog(parent), timer(new QTimer(this))
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 启动定时器
    this->timer->start(3 * 1000);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

SensorDialog::~SensorDialog()
{

}

// 界面字符串
void SensorDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.leLyse, "IDS_LYSE");
    this->setText(ui.leDiluent, "IDS_DILUENT");
    this->setText(ui.leWaste, "IDS_WASTE");

    this->setText(ui.pbOk, "IDS_OK");
}

// 定时器超时
void SensorDialog::onTimerOut()
{
    bool hasLyse = Timeseq::hasLyse();
    this->setText(ui.leLyse, (hasLyse ? "IDS_YES" : "IDS_NO"));

    bool hasDiluent = Timeseq::hasDiluent();
    this->setText(ui.leDiluent, (hasDiluent ? "IDS_YES" : "IDS_NO"));

    bool wasteFull = Timeseq::isWasteFull();
    this->setText(ui.leWaste, (wasteFull ? "IDS_YES" : "IDS_NO"));
}