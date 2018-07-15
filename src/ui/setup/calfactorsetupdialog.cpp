#include <QtDebug>

#include "cache.h"
#include "print.h"
#include "datetime.h"
#include "paraname.h"
#include "calfactorxml.h"
#include "calfactorsetupdialog.h"


// 校准系数范围
#define LOW_FACTOR          (0.4f)
#define HIGH_FACTOR         (1.6f)


CalFactorSetupDialog::CalFactorSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // 界面控件
    QMap<QString, QLineEdit*> peripheralDateEdits;
    peripheralDateEdits.insert(PARA_WBC, ui.lePeripheralWbcDate);
    peripheralDateEdits.insert(PARA_RBC, ui.lePeripheralRbcDate);
    peripheralDateEdits.insert(PARA_PLT, ui.lePeripheralPltDate);
    peripheralDateEdits.insert(PARA_HGB, ui.lePeripheralHgbDate);
    peripheralDateEdits.insert(PARA_MCV, ui.lePeripheralMcvDate);

    this->peripheralValueEdits.insert(PARA_WBC, ui.lePeripheralWbcFactor);
    this->peripheralValueEdits.insert(PARA_RBC, ui.lePeripheralRbcFactor);
    this->peripheralValueEdits.insert(PARA_PLT, ui.lePeripheralPltFactor);
    this->peripheralValueEdits.insert(PARA_HGB, ui.lePeripheralHgbFactor);
    this->peripheralValueEdits.insert(PARA_MCV, ui.lePeripheralMcvFactor);

    QMap<QString, QLineEdit*> prediluentDateEdits;
    prediluentDateEdits.insert(PARA_WBC, ui.lePrediluentWbcDate);
    prediluentDateEdits.insert(PARA_RBC, ui.lePrediluentRbcDate);
    prediluentDateEdits.insert(PARA_PLT, ui.lePrediluentPltDate);
    prediluentDateEdits.insert(PARA_HGB, ui.lePrediluentHgbDate);
    prediluentDateEdits.insert(PARA_MCV, ui.lePrediluentMcvDate);

    this->prediluentValueEdits.insert(PARA_WBC, ui.lePrediluentWbcFactor);
    this->prediluentValueEdits.insert(PARA_RBC, ui.lePrediluentRbcFactor);
    this->prediluentValueEdits.insert(PARA_PLT, ui.lePrediluentPltFactor);
    this->prediluentValueEdits.insert(PARA_HGB, ui.lePrediluentHgbFactor);
    this->prediluentValueEdits.insert(PARA_MCV, ui.lePrediluentMcvFactor);

    QMap<QString, QLineEdit*> wholeBloodDateEdits;
    wholeBloodDateEdits.insert(PARA_WBC, ui.leWholeBloodWbcDate);
    wholeBloodDateEdits.insert(PARA_RBC, ui.leWholeBloodRbcDate);
    wholeBloodDateEdits.insert(PARA_PLT, ui.leWholeBloodPltDate);
    wholeBloodDateEdits.insert(PARA_HGB, ui.leWholeBloodHgbDate);
    wholeBloodDateEdits.insert(PARA_MCV, ui.leWholeBloodMcvDate);

    this->wholeBloodValueEdits.insert(PARA_WBC, ui.leWholeBloodWbcFactor);
    this->wholeBloodValueEdits.insert(PARA_RBC, ui.leWholeBloodRbcFactor);
    this->wholeBloodValueEdits.insert(PARA_PLT, ui.leWholeBloodPltFactor);
    this->wholeBloodValueEdits.insert(PARA_HGB, ui.leWholeBloodHgbFactor);
    this->wholeBloodValueEdits.insert(PARA_MCV, ui.leWholeBloodMcvFactor);

    // 读取校准系数值
    const QString key1 = this->key1();
    {
        QList<CalFactor> calFactors = Cache::getCalFactors(key1, KEY2_WHOLE_BLOOD);

        // 界面显示
        foreach (CalFactor calFactor, calFactors)
        {
            QString id = calFactor.id;

            // 校准日期
            if (wholeBloodDateEdits.contains(id))
            {
                QLineEdit* lineEdit = wholeBloodDateEdits.value(id);
                if (lineEdit)
                {
                    QDate date = DateTime::dateFromStringD(calFactor.date);
                    lineEdit->setText(DateTime::dateToStringC(date));
                }
            }

            // 校准系数
            if (this->wholeBloodValueEdits.contains(id))
            {
                DigitLineEdit* lineEdit = this->wholeBloodValueEdits.value(id);
                if (lineEdit)
                {
                    lineEdit->setFormat(1, 3);
                    lineEdit->setRange(LOW_FACTOR, HIGH_FACTOR);
                    lineEdit->setValue(calFactor.value);
                }
            }
        }
    }

    {
        QList<CalFactor> calFactors = Cache::getCalFactors(key1, KEY2_PERIPHERAL);

        // 界面显示
        foreach (CalFactor calFactor, calFactors)
        {
            QString id = calFactor.id;

            // 校准日期
            if (peripheralDateEdits.contains(id))
            {
                QLineEdit* lineEdit = peripheralDateEdits.value(id);
                if (lineEdit)
                {
                    QDate date = DateTime::dateFromStringD(calFactor.date);
                    lineEdit->setText(DateTime::dateToStringC(date));
                }
            }

            // 校准系数
            if (this->peripheralValueEdits.contains(id))
            {
                DigitLineEdit* lineEdit = this->peripheralValueEdits.value(id);
                if (lineEdit)
                {
                    lineEdit->setFormat(1, 3);
                    lineEdit->setRange(LOW_FACTOR, HIGH_FACTOR);
                    lineEdit->setValue(calFactor.value);
                }
            }
        }
    }

    {
        QList<CalFactor> calFactors = Cache::getCalFactors(key1, KEY2_PREDILUENT);

        // 界面显示
        foreach (CalFactor calFactor, calFactors)
        {
            QString id = calFactor.id;

            // 校准日期
            if (prediluentDateEdits.contains(id))
            {
                QLineEdit* lineEdit = prediluentDateEdits.value(id);
                if (lineEdit)
                {
                    QDate date = DateTime::dateFromStringD(calFactor.date);
                    lineEdit->setText(DateTime::dateToStringC(date));
                }
            }

            // 校准系数
            if (this->prediluentValueEdits.contains(id))
            {
                DigitLineEdit* lineEdit = this->prediluentValueEdits.value(id);
                if (lineEdit)
                {
                    lineEdit->setFormat(1, 3);
                    lineEdit->setRange(LOW_FACTOR, HIGH_FACTOR);
                    lineEdit->setValue(calFactor.value);
                }
            }
        }
    }

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

CalFactorSetupDialog::~CalFactorSetupDialog()
{

}

// 从界面获取设置信息
void CalFactorSetupDialog::getSetupInfoFromUI()
{
    this->wholeBloodValues.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->wholeBloodValueEdits.begin(); iter != this->wholeBloodValueEdits.end(); iter++)
    {
        QString id = iter.key();

        DigitLineEdit* valueEdit = this->wholeBloodValueEdits.value(id);
        if (valueEdit)
        {
            this->wholeBloodValues.insert(id, valueEdit->value());
        }
    }

    this->peripheralValues.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->peripheralValueEdits.begin(); iter != this->peripheralValueEdits.end(); iter++)
    {
        QString id = iter.key();

        DigitLineEdit* valueEdit = this->peripheralValueEdits.value(id);
        if (valueEdit)
        {
            this->peripheralValues.insert(id, valueEdit->value());
        }
    }

    this->prediluentValues.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->prediluentValueEdits.begin(); iter != this->prediluentValueEdits.end(); iter++)
    {
        QString id = iter.key();

        DigitLineEdit* valueEdit = this->prediluentValueEdits.value(id);
        if (valueEdit)
        {
            this->prediluentValues.insert(id, valueEdit->value());
        }
    }
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString CalFactorSetupDialog::isSetupInfoValid()
{
    for (QMap<QString, float>::iterator iter = this->wholeBloodValues.begin(); iter != this->wholeBloodValues.end(); iter++)
    {
        float value = iter.value();
        if (value < LOW_FACTOR || HIGH_FACTOR < value)
        {
            DigitLineEdit* valueEdit = this->wholeBloodValueEdits.value(iter.key());
            return QString::number((int)valueEdit);
        }
    }

    for (QMap<QString, float>::iterator iter = this->peripheralValues.begin(); iter != this->peripheralValues.end(); iter++)
    {
        float value = iter.value();
        if (value < LOW_FACTOR || HIGH_FACTOR < value)
        {
            DigitLineEdit* valueEdit = this->peripheralValueEdits.value(iter.key());
            return QString::number((int)valueEdit);
        }
    }

    for (QMap<QString, float>::iterator iter = this->prediluentValues.begin(); iter != this->prediluentValues.end(); iter++)
    {
        float value = iter.value();
        if (value < LOW_FACTOR || HIGH_FACTOR < value)
        {
            DigitLineEdit* valueEdit = this->prediluentValueEdits.value(iter.key());
            return QString::number((int)valueEdit);
        }
    }

    return QString();
}

// 设置信息无效处理（提示信息）
QString CalFactorSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return "Invalid factor";
}

QWidget* CalFactorSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return (DigitLineEdit*)(ret.toInt());
}

// 设置信息有效处理（保存设置信息）
bool CalFactorSetupDialog::onSetupInfoValid()
{
    bool ret = false;

    do 
    {
        // 加载配置文件
        CalFactorXml calFactorXml;
        if (!calFactorXml.load())
        {
            qWarning() << "CalFactorSetupDialog onSetupInfoValid load fail";
            break;
        }

        const QString key1 = this->key1();
        {
            QString key2 = KEY2_WHOLE_BLOOD;

            // 修改前后校准系数
            QList<CalFactor> modCalFactors;
            QList<CalFactor> newAllCalFactors;
            QList<CalFactor> oldAllCalFactors = calFactorXml.getCalFactors(key1, key2);

            foreach (CalFactor calFactor, oldAllCalFactors)
            {
                QString id = calFactor.id;

                if (this->wholeBloodValues.contains(id))
                {
                    float value = this->wholeBloodValues.value(calFactor.id);
                    if (calFactor.value != value)
                    {
                        calFactor.value = value;
                        calFactor.date = DateTime::dateToStringD(QDate::currentDate());

                        modCalFactors.append(calFactor);
                    }

                    newAllCalFactors.append(calFactor);
                }
            }

            if (!modCalFactors.isEmpty())
            {
                // 保存校准系数
                if (!calFactorXml.setCalFactors(key1, key2, modCalFactors))
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid setCalFactors fail";
                    break;
                }
                if (!calFactorXml.save())
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid save fail";
                    break;
                }

                // 更新缓存
                Cache::setCalFactors(key1, key2, newAllCalFactors);
            }
        }

        {
            QString key2 = KEY2_PERIPHERAL;

            // 修改前后校准系数
            QList<CalFactor> modCalFactors;
            QList<CalFactor> newAllCalFactors;
            QList<CalFactor> oldAllCalFactors = calFactorXml.getCalFactors(key1, key2);

            foreach (CalFactor calFactor, oldAllCalFactors)
            {
                QString id = calFactor.id;

                if (this->peripheralValues.contains(id))
                {
                    float value = this->peripheralValues.value(calFactor.id);
                    if (calFactor.value != value)
                    {
                        calFactor.value = value;
                        calFactor.date = DateTime::dateToStringD(QDate::currentDate());

                        modCalFactors.append(calFactor);
                    }
                }

                newAllCalFactors.append(calFactor);
            }

            // 保存校准系数
            if (!modCalFactors.isEmpty())
            {
                if (!calFactorXml.setCalFactors(key1, key2, modCalFactors))
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid setCalFactors fail";
                    break;
                }
                if (!calFactorXml.save())
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid save fail";
                    break;
                }

                // 更新缓存
                Cache::setCalFactors(key1, key2, newAllCalFactors);
            }
        }

        {
            QString key2 = KEY2_PREDILUENT;

            // 修改前后校准系数
            QList<CalFactor> modCalFactors;
            QList<CalFactor> newAllCalFactors;
            QList<CalFactor> oldAllCalFactors = calFactorXml.getCalFactors(key1, key2);

            foreach (CalFactor calFactor, oldAllCalFactors)
            {
                QString id = calFactor.id;

                if (this->prediluentValues.contains(id))
                {
                    float value = this->prediluentValues.value(calFactor.id);
                    if (calFactor.value != value)
                    {
                        calFactor.value = value;
                        calFactor.date = DateTime::dateToStringD(QDate::currentDate());

                        modCalFactors.append(calFactor);
                    }
                }

                newAllCalFactors.append(calFactor);
            }

            // 保存校准系数
            if (!modCalFactors.isEmpty())
            {
                if (!calFactorXml.setCalFactors(key1, key2, modCalFactors))
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid setCalFactors fail";
                    break;
                }
                if (!calFactorXml.save())
                {
                    qWarning() << "CalFactorSetupDialog onSetupInfoValid save fail";
                    break;
                }

                // 更新缓存
                Cache::setCalFactors(key1, key2, newAllCalFactors);
            }
        }

        ret = true;
    } while (0);

    return ret;
}

// 按钮点击
void CalFactorSetupDialog::onBtnPrintClicked()
{
    // 获取校准系数
    const QString key1 = this->key1();

    const QList<CalFactor> peripheralCalFactors = Cache::getCalFactors(key1, KEY2_PERIPHERAL);
    const QList<CalFactor> prediluentCalFactors = Cache::getCalFactors(key1, KEY2_PREDILUENT);
    const QList<CalFactor> wholeBloodCalFactors = Cache::getCalFactors(key1, KEY2_WHOLE_BLOOD);

    // 打印
    Print print;
    print.printCalFactors(peripheralCalFactors, prediluentCalFactors, wholeBloodCalFactors);
}

// 关键字
QString CalFactorSetupDialog::key1() const
{
    const User* user = Cache::currentUser();
    return (user && user->isService() ? KEY1_FACTORY : KEY1_USER);
}