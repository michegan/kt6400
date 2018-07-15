#include <QtDebug>

#include "dma.h"
#include "hal.h"
#include "gainxml.h"
#include "halfpga.h"
#include "utility.h"
#include "gainsetupdialog.h"


GainSetupDialog::GainSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent), timer(new QTimer(this))
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    // ��������
    this->cmds.insert(KEY2_WBC, WBC_GAIN);
    this->cmds.insert(KEY2_RBC, RBC_GAIN);
    this->cmds.insert(KEY2_HGB, HGB_GAIN);

    // ��ȡ����ֵ
    GainXml gainXml;
    if (gainXml.load())
    {
        ui.leWbc->setText(gainXml.getTextValue2(KEY1_GAIN, KEY2_WBC));
        ui.leRbc->setText(gainXml.getTextValue2(KEY1_GAIN, KEY2_RBC));
        ui.leHgb->setText(gainXml.getTextValue2(KEY1_GAIN, KEY2_HGB));
    }
    else
    {
        qWarning() << "GainSetupDialog GainSetupDialog load fail";
    }

    // �����źŲ�
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    // 3�붨ʱ
    this->timer->start(3 * 1000);
}

GainSetupDialog::~GainSetupDialog()
{

}

// �����ַ���
void GainSetupDialog::setWindowText()
{
    // ���ദ��
    SetupDialog::setWindowText();

    // ���ദ��
    this->setText(ui.lbHgbAd, "IDS_HGB_AD");

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// �ӽ����ȡ������Ϣ
void GainSetupDialog::getSetupInfoFromUI()
{
    this->gains.clear();

    this->gains.insert(KEY2_WBC, ui.leWbc->text());
    this->gains.insert(KEY2_RBC, ui.leRbc->text());
    this->gains.insert(KEY2_HGB, ui.leHgb->text());
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString GainSetupDialog::isSetupInfoValid()
{
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString GainSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* GainSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// ������Ϣ��Ч��������������Ϣ��
bool GainSetupDialog::onSetupInfoValid()
{
    // ��ȡ����ֵ
    GainXml gainXml;
    if (!gainXml.load())
    {
        qWarning() << "GainSetupDialog onSetupInfoValid gainXml load fail";
        return false;
    }

    // �������棨����ֵ��
    QStringList keys = this->gains.keys();
    foreach (QString key, keys)
    {
        int cmd = this->cmds.value(key);
        QString value = this->gains.value(key);

        qDebug() << "GainSetupDialog onSetupInfoValid setGain" << key << value;

        if (HalFpga::write_addr(cmd, value.toInt()))
        {
            if (gainXml.setTextValue2(KEY1_GAIN, key, value))
            {
                if (gainXml.save())
                {

                }
                else
                {
                    qWarning() << "GainSetupDialog onSetupInfoValid save fail";
                    return false;
                }
            }
            else
            {
                qWarning() << "GainSetupDialog onSetupInfoValid setTextValue2 fail";
                return false;
            }
        }
        else
        {
            qWarning() << "GainSetupDialog onSetupInfoValid write fail";
            return false;
        }
    }

    return true;
}

// ��ʱ����ʱ
void GainSetupDialog::onTimerOut()
{
    HalFpga::write(HGB_BK_COLLECT);

    // �ȴ�1��
    Utility::ssleep(1);

    // ��ȡADֵ
    DmaBuf* dmaBuf = Dma::getDmaBuf();
    if (dmaBuf)
    {
        ui.leHgbAd->setText(QString::number(dmaBuf->hgbBkVoltage));
    }
}