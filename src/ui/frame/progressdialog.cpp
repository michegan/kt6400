#include <QtDebug>

#include "enum.h"
#include "progressdialog.h"


ProgressDialog::ProgressDialog(QWidget* parent)
    : Dialog(parent), timer(new QTimer(this))
{
    ui.setupUi(this);

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

ProgressDialog::~ProgressDialog()
{

}

// ִ��
void ProgressDialog::exec(float time)
{
    qDebug() << "ProgressDialog exec" << time;

    // ������Ϣ
    ui.pbProgress->setValue(0);
    ui.pbProgress->setMaximum(time);

    // ������ʱ��
    this->timer->start(1000);

    // ģ̬�Ի���
    Dialog::exec();
}

// �û���ʾ
void ProgressDialog::setText(const QString& text)
{
    ui.lbNotification->setText(text);
}

// ��ʱ����ʱ
void ProgressDialog::onTimerOut()
{
    int value = ui.pbProgress->value();
    int maximum = ui.pbProgress->maximum();

    qDebug() << "ProgressDialog onTimerOut" << value << maximum;

    ui.pbProgress->setValue(value + 1);
}