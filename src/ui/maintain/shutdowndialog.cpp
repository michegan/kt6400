#include "shutdowndialog.h"


ShutDownDialog::ShutDownDialog(QWidget* parent)
    : Dialog(parent), steps(0), timer(new QTimer(this))
{
    ui.setupUi(this);

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    // ��ʱ��
    this->timer->start(50);
}

ShutDownDialog::~ShutDownDialog()
{

}

// ��ť���
void ShutDownDialog::onTimerOut()
{
    this->steps ++;
    ui.pbProgress->setValue(this->steps);

    if (100 <= this->steps)
    {
        ui.pbProgress->hide();
        this->timer->stop();
        ui.lbNote->setText("Please turnoff the power");
    }
}