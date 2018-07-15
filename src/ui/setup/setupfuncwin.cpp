#include <QtDebug>
#include <QMessageBox>

#include "setupfuncwin.h"


SetupFuncWin::SetupFuncWin(QWidget* parent)
    : FuncWin(parent)
{
    // ����״̬��
    this->createStatusBar();
}

SetupFuncWin::~SetupFuncWin()
{

}

// �л������ܴ���
void SetupFuncWin::switchToFuncWin(FuncWin* funcWin)
{
    // �ӽ����ȡ������Ϣ
    this->getSetupInfoFromUI();

    // ������Ϣ�Ƿ�仯
    if (this->isSetupInfoChanged())
    {
        QMessageBox::StandardButton button = QMessageBox::question(this, "Confirm", "Save or not?", 
                                                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        if (QMessageBox::Yes == button)
        {
            // ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
            QString ret = this->isSetupInfoValid();
            qDebug() << "SetupFuncWin switchToFuncWin" << ret;

            if (ret.isEmpty())
            {
                // ������Ϣ��Ч��������������Ϣ��
                if (this->onSetupInfoValid())
                {
                    // ����ɹ����˳����ý���
                    FuncWin::switchToFuncWin(funcWin);
                }
                else
                {
                    // ����ʧ�ܣ���ʾ�û�
                    QMessageBox::warning(this, "Warning", "Save failed");
                }
            }
            else
            {
                // ������Ϣ��Ч������ʾ��Ϣ��
                QString text = this->onSetupInfoInvalidText(ret);
                QMessageBox::warning(this, "Warning", text);

                // ������Ϣ��Ч������Ч�ؼ���
                QWidget* widget = this->onSetupInfoInvalidWidget(ret);
                if (widget)
                {
                    widget->setFocus();
                }
            }
        }
        else if (QMessageBox::No == button)
        {
            // �����棬�˳����ý���
            FuncWin::switchToFuncWin(funcWin);
        }
        else
        {
            // ȡ����ͣ�������ý���
        }
    }
    else
    {
        // ������Ϣδ�仯����ֱ���л�
        FuncWin::switchToFuncWin(funcWin);
    }
}