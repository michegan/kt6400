#include <QtDebug>

#include "enum.h"
#include "progressdialog.h"


ProgressDialog::ProgressDialog(QWidget* parent)
    : Dialog(parent), timer(new QTimer(this))
{
    ui.setupUi(this);

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

ProgressDialog::~ProgressDialog()
{

}

// 执行
void ProgressDialog::exec(float time)
{
    qDebug() << "ProgressDialog exec" << time;

    // 进度信息
    ui.pbProgress->setValue(0);
    ui.pbProgress->setMaximum(time);

    // 启动定时器
    this->timer->start(1000);

    // 模态对话框
    Dialog::exec();
}

// 用户提示
void ProgressDialog::setText(const QString& text)
{
    ui.lbNotification->setText(text);
}

// 定时器超时
void ProgressDialog::onTimerOut()
{
    int value = ui.pbProgress->value();
    int maximum = ui.pbProgress->maximum();

    qDebug() << "ProgressDialog onTimerOut" << value << maximum;

    ui.pbProgress->setValue(value + 1);
}