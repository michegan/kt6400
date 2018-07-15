#include <QtDebug>
#include <QResizeEvent>

#include "msgboxdialog.h"


MsgBoxDialog::MsgBoxDialog(const QString& text, QMessageBox::StandardButton btn1, QMessageBox::StandardButton btn2, QWidget* parent)
    : Dialog(parent), button(btn1), button1(btn1), button2(btn2)
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ��ʾ�ı�
    ui.teMessage->setText(text);
    qDebug() << "MsgBoxDialog MsgBoxDialog" << text;

    // ��ť�ɼ���
    ui.pbButton1->setVisible(QMessageBox::NoButton != btn1);
    ui.pbButton2->setVisible(QMessageBox::NoButton != btn2);

    // ͨ��ָ�����㣬����Ӵﵽ�ر�����̵�Ŀ�ģ�ȷ������̺���Ϣ�򲻻�ͬʱ����
    if (QMessageBox::NoButton != btn1)
    {
        ui.pbButton1->setFocus();
    }
    else if (QMessageBox::NoButton != btn2)
    {
        ui.pbButton2->setFocus();
    }

    // �����źŲ�
    connect(ui.pbButton1, SIGNAL(clicked()), this, SLOT(onBtnButton1Clicked()));
    connect(ui.pbButton2, SIGNAL(clicked()), this, SLOT(onBtnButton2Clicked()));
}

MsgBoxDialog::~MsgBoxDialog()
{

}

// �û�ѡ��
QMessageBox::StandardButton MsgBoxDialog::select() const
{
    return this->button;
}

// �����ַ���
void MsgBoxDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbButton1, this->buttonText(this->button1));
    this->setText(ui.pbButton2, this->buttonText(this->button2));
}

// �ߴ�仯
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

// ��ť���
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

// ��ť�ı�
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