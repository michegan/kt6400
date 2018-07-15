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

    // 界面字符串
    this->setWindowText();

    // 设置命令
    this->cmds.insert(KEY2_WBC, WBC_GAIN);
    this->cmds.insert(KEY2_RBC, RBC_GAIN);
    this->cmds.insert(KEY2_HGB, HGB_GAIN);

    // 读取增益值
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

    // 关联信号槽
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    // 3秒定时
    this->timer->start(3 * 1000);
}

GainSetupDialog::~GainSetupDialog()
{

}

// 界面字符串
void GainSetupDialog::setWindowText()
{
    // 基类处理
    SetupDialog::setWindowText();

    // 子类处理
    this->setText(ui.lbHgbAd, "IDS_HGB_AD");

    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 从界面获取设置信息
void GainSetupDialog::getSetupInfoFromUI()
{
    this->gains.clear();

    this->gains.insert(KEY2_WBC, ui.leWbc->text());
    this->gains.insert(KEY2_RBC, ui.leRbc->text());
    this->gains.insert(KEY2_HGB, ui.leHgb->text());
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString GainSetupDialog::isSetupInfoValid()
{
    return QString();
}

// 设置信息无效处理（提示信息）
QString GainSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* GainSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// 设置信息有效处理（保存设置信息）
bool GainSetupDialog::onSetupInfoValid()
{
    // 读取增益值
    GainXml gainXml;
    if (!gainXml.load())
    {
        qWarning() << "GainSetupDialog onSetupInfoValid gainXml load fail";
        return false;
    }

    // 设置增益（增益值）
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

// 定时器超时
void GainSetupDialog::onTimerOut()
{
    HalFpga::write(HGB_BK_COLLECT);

    // 等待1秒
    Utility::ssleep(1);

    // 读取AD值
    DmaBuf* dmaBuf = Dma::getDmaBuf();
    if (dmaBuf)
    {
        ui.leHgbAd->setText(QString::number(dmaBuf->hgbBkVoltage));
    }
}