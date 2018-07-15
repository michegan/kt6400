#include <QtDebug>
#include <QResizeEvent>

#include "msgboxdialog.h"


MsgBoxDialog::MsgBoxDialog(const QString& text, QMessageBox::StandardButton btn1, QMessageBox::StandardButton btn2, QWidget* parent)
    : Dialog(parent), button(btn1), button1(btn1), button2(btn2)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 提示文本
    ui.teMessage->setText(text);
    qDebug() << "MsgBoxDialog MsgBoxDialog" << text;

    // 按钮可见性
    ui.pbButton1->setVisible(QMessageBox::NoButton != btn1);
    ui.pbButton2->setVisible(QMessageBox::NoButton != btn2);

    // 通过指定焦点，来间接达到关闭软键盘的目的，确保软键盘和消息框不会同时出现
    if (QMessageBox::NoButton != btn1)
    {
        ui.pbButton1->setFocus();
    }
    else if (QMessageBox::NoButton != btn2)
    {
        ui.pbButton2->setFocus();
    }

    // 关联信号槽
    connect(ui.pbButton1, SIGNAL(clicked()), this, SLOT(onBtnButton1Clicked()));
    connect(ui.pbButton2, SIGNAL(clicked()), this, SLOT(onBtnButton2Clicked()));
}

MsgBoxDialog::~MsgBoxDialog()
{

}

// 用户选项
QMessageBox::StandardButton MsgBoxDialog::select() const
{
    return this->button;
}

// 界面字符串
void MsgBoxDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    this->setText(ui.pbButton1, this->buttonText(this->button1));
    this->setText(ui.pbButton2, this->buttonText(this->button2));
}

// 尺寸变化
void MsgBoxDialog::resizeEvent(QResizeEvent* event)
{
    Dialog::resizeEvent(event);

    if (QMessageBox::NoButton == this->button1 || QMessageBox::NoButton == this->button2)
    {
        float x1 = (event->size().width() - ui.pbButton1->width()) / 2;
        ui.pbButton1->move(x1, ui.pbButton1->y());

        float x2 = (event->size().width() - ui.pbButton2->width()) / 2;
        ui.pbButton2->move(x2, ui.pbButton1->y());
    }
}

// 按钮点击
void MsgBoxDialog::onBtnButton1Clicked()
{
    this->button = this->button1;
    this->accept();
}

void MsgBoxDialog::onBtnButton2Clicked()
{
    this->button = this->button2;
    this->accept();
}

// 按钮文本
QString MsgBoxDialog::buttonText(QMessageBox::StandardButton btn)
{
    if (QMessageBox::Ok == btn)
    {
        return ("IDS_OK");
    }
    else if (QMessageBox::Yes == btn)
    {
        return ("IDS_YES");
    }
    else if (QMessageBox::No == btn)
    {
        return ("IDS_NO");
    }
    else
    {
        return ("IDS_NULL");
    }
}