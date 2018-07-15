#include <QtDebug>

#include "messagebox.h"
#include "setupdialog.h"


SetupDialog::SetupDialog(QWidget* parent)
    : Dialog(parent)
{

}

SetupDialog::~SetupDialog()
{

}

// ��ť���
void SetupDialog::onBtnOkClicked()
{
    // �ӽ����ȡ������Ϣ
    this->getSetupInfoFromUI();

    // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
    QString ret = this->isSetupInfoValid();
    qDebug() << "SetupDialog onBtnOkClicked" << ret;

    if (ret.isEmpty())
    {
        // ������Ϣ��Ч��������������Ϣ��
        if (this->onSetupInfoValid())
        {
            // ����ɹ����˳����ý���
            this->accept();
        }
        else
        {
            // ����ʧ�ܣ���ʾ�û�
            MessageBox::warning(this, "Save failed.");
        }
    }
    else
    {
        // ������Ϣ��Ч������ʾ��Ϣ��
        QString text = this->onSetupInfoInvalidText(ret);
        MessageBox::warning(this, text);

        // ������Ϣ��Ч������Ч�ؼ���
        QWidget* widget = this->onSetupInfoInvalidWidget(ret);
        if (widget)
        {
            widget->setFocus();
        }
    }
}

void SetupDialog::onBtnCancelClicked()
{
    this->reject();
}