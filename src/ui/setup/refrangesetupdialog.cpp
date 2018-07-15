#include <QtDebug>

#include "cache.h"
#include "xmlnode.h"
#include "paraname.h"
#include "machinexml.h"
#include "sampleinfo.h"
#include "refrangexml.h"
#include "refrangesetupdialog.h"


RefRangeSetupDialog::RefRangeSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // 编辑框
    this->lowEdits.insert(PARA_WBC, ui.leWbcLow);
    this->lowEdits.insert(PARA_LYM_PER, ui.leLymPerLow);
    this->lowEdits.insert(PARA_MID_PER, ui.leMidPerLow);
    this->lowEdits.insert(PARA_GRAN_PER, ui.leGranPerLow);
    this->lowEdits.insert(PARA_LYM_NUM, ui.leLymNumLow);
    this->lowEdits.insert(PARA_MID_NUM, ui.leMidNumLow);
    this->lowEdits.insert(PARA_GRAN_NUM, ui.leGranNumLow);
    this->lowEdits.insert(PARA_RBC, ui.leRbcLow);
    this->lowEdits.insert(PARA_HGB, ui.leHgbLow);
    this->lowEdits.insert(PARA_HCT, ui.leHctLow);
    this->lowEdits.insert(PARA_MCH, ui.leMchLow);
    this->lowEdits.insert(PARA_MCV, ui.leMcvLow);
    this->lowEdits.insert(PARA_MCHC, ui.leMchcLow);
    this->lowEdits.insert(PARA_RDW_CV, ui.leRdwCvLow);
    this->lowEdits.insert(PARA_RDW_SD, ui.leRdwSdLow);
    this->lowEdits.insert(PARA_PLT, ui.lePltLow);
    this->lowEdits.insert(PARA_MPV, ui.leMpvLow);
    this->lowEdits.insert(PARA_PCT, ui.lePctLow);
    this->lowEdits.insert(PARA_PDW, ui.lePdwLow);
    this->lowEdits.insert(PARA_PLCC, ui.lePlccLow);
    this->lowEdits.insert(PARA_PLCR, ui.lePlcrLow);

    this->highEdits.insert(PARA_WBC, ui.leWbcHigh);
    this->highEdits.insert(PARA_LYM_PER, ui.leLymPerHigh);
    this->highEdits.insert(PARA_MID_PER, ui.leMidPerHigh);
    this->highEdits.insert(PARA_GRAN_PER, ui.leGranPerHigh);
    this->highEdits.insert(PARA_LYM_NUM, ui.leLymNumHigh);
    this->highEdits.insert(PARA_MID_NUM, ui.leMidNumHigh);
    this->highEdits.insert(PARA_GRAN_NUM, ui.leGranNumHigh);
    this->highEdits.insert(PARA_RBC, ui.leRbcHigh);
    this->highEdits.insert(PARA_HGB, ui.leHgbHigh);
    this->highEdits.insert(PARA_HCT, ui.leHctHigh);
    this->highEdits.insert(PARA_MCH, ui.leMchHigh);
    this->highEdits.insert(PARA_MCV, ui.leMcvHigh);
    this->highEdits.insert(PARA_MCHC, ui.leMchcHigh);
    this->highEdits.insert(PARA_RDW_CV, ui.leRdwCvHigh);
    this->highEdits.insert(PARA_RDW_SD, ui.leRdwSdHigh);
    this->highEdits.insert(PARA_PLT, ui.lePltHigh);
    this->highEdits.insert(PARA_MPV, ui.leMpvHigh);
    this->highEdits.insert(PARA_PCT, ui.lePctHigh);
    this->highEdits.insert(PARA_PDW, ui.lePdwHigh);
    this->highEdits.insert(PARA_PLCC, ui.lePlccHigh);
    this->highEdits.insert(PARA_PLCR, ui.lePlcrHigh);

    // 机型配置
    bool forPets = Cache::isForPets();

    // 根据机型显示隐藏部分控件
    ui.lbSpecies->setVisible(forPets);
    ui.cbSpecies->setVisible(forPets);

    // 参考组配置
    if (forPets)
    {
        this->keys1 = Cache::refRangeKeys1();
        this->keys1.removeOne("IDS_HUMAN");
    }
    else
    {
        this->keys1.append("IDS_HUMAN");
    }
        
    // 下拉框选项
    foreach (QString key1, this->keys1)
    {
        ui.cbSpecies->addItem(this->getString(key1));
    }

    // 默认第一个物种类型第一个参考组
    this->onSpeciesComboBoxCurrentIndexChanged(0);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(ui.cbGroup, SIGNAL(currentIndexChanged(int)), this, SLOT(onGroupComboBoxCurrentIndexChanged(int)));
    connect(ui.cbSpecies, SIGNAL(currentIndexChanged(int)), this, SLOT(onSpeciesComboBoxCurrentIndexChanged(int)));
}

RefRangeSetupDialog::~RefRangeSetupDialog()
{

}

// 从界面获取设置信息
void RefRangeSetupDialog::getSetupInfoFromUI()
{
    // 参考范围下限（修改后）
    this->lowLimits.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->lowEdits.begin(); iter != this->lowEdits.end(); iter++)
    {
        DigitLineEdit* lineEdit = iter.value();
        if (lineEdit)
        {
            this->lowLimits.appendPara(iter.key(), lineEdit->value());
        }
    }

    // 参考范围上限（修改后）
    this->highLimits.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->highEdits.begin(); iter != this->highEdits.end(); iter++)
    {
        DigitLineEdit* lineEdit = iter.value();
        if (lineEdit)
        {
            this->highLimits.appendPara(iter.key(), lineEdit->value());
        }
    }
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString RefRangeSetupDialog::isSetupInfoValid()
{
    foreach (Para para, this->lowLimits)
    {
        float low = para.value;
        float high = this->highLimits.paraValue(para.name);

        if (high <= low)
        {
            return para.name;
        }
    }
    return QString();
}

// 设置信息无效处理（提示信息）
QString RefRangeSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return (ret + " invalid");
}

QWidget* RefRangeSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return this->lowEdits.value(ret, 0);
}

// 设置信息有效处理（保存设置信息）
bool RefRangeSetupDialog::onSetupInfoValid()
{
    bool ret = false;

    // 参考组配置
    RefRangeXml xml;
    if (xml.load())
    {
        // 当前参考组配置关键字
        QString key1 = this->keys1.at(ui.cbSpecies->currentIndex());
        QString key2 = this->keys2.at(ui.cbGroup->currentIndex());

        // 参考范围下限（修改后）
        XmlNode* xmlNode2 = xml.getNode2(key1, key2);
        if (xmlNode2)
        {
            foreach (Para para, this->lowLimits)
            {
                XmlNode* xmlNode3 = xmlNode2->child(para.name);
                if (xmlNode3)
                {
                    xmlNode3->setAttribute(ATTR_LOW, para.valueToString(2));
                }
                else
                {
                    qWarning() << "RefRangeSetupDialog onSetupInfoValid child fail" << key1 << key2 << para.name;
                }
            }

            // 参考范围上限（修改后）
            foreach (Para para, this->highLimits)
            {
                XmlNode* xmlNode3 = xmlNode2->child(para.name);
                if (xmlNode3)
                {
                    xmlNode3->setAttribute(ATTR_HIGH, para.valueToString(2));
                }
                else
                {
                    qWarning() << "RefRangeSetupDialog onSetupInfoValid child fail" << key1 << key2 << para.name;
                }
            }

            ret = xml.save();
            if (ret)
            {
                Cache::setRefRange(key1, key2, this->lowLimits, this->highLimits);
            }
            else
            {
                qWarning() << "RefRangeSetupDialog onSetupInfoValid save fail";
            }
        }
        else
        {
            qWarning() << "RefRangeSetupDialog onSetupInfoValid getNode2 fail" << key1 << key2;
        }
    }
    else
    {
        qWarning() << "RefRangeSetupDialog onSetupInfoValid load fail";
    }

    return ret;
}

// 下拉框当前选项变化
void RefRangeSetupDialog::onGroupComboBoxCurrentIndexChanged(int index)
{
    qDebug() << "RefRangeSetupDialog onGroupComboBoxCurrentIndexChanged" << index;

    do 
    {
        // 所有有效性检测
        if (index < 0 || this->keys2.length() <= index)
        {
            qWarning() << "RefRangeSetupDialog onGroupComboBoxCurrentIndexChanged invalid index";
            break;
        }

        // 当前参考组配置关键字
        QString key1 = this->keys1.at(ui.cbSpecies->currentIndex());
        QString key2 = this->keys2.at(index);

        ParaList lowLimits;
        ParaList highLimits;
        if (!Cache::refRange(key1, key2, lowLimits, highLimits))
        {
            qWarning() << "RefRangeSetupDialog onGroupComboBoxCurrentIndexChanged refRange fail";
            break;
        }

        for (QMap<QString, DigitLineEdit*>::iterator iter = this->lowEdits.begin(); iter != this->lowEdits.end(); iter++)
        {
            QString key3 = iter.key();

            DigitLineEdit* lineEdit = iter.value();
            if (lineEdit)
            {
                lineEdit->setFormat(3, 2);
                lineEdit->setValue(lowLimits.paraValue(key3));
            }
        }

        // 参考范围上限
        for (QMap<QString, DigitLineEdit*>::iterator iter = this->highEdits.begin(); iter != this->highEdits.end(); iter++)
        {
            QString key3 = iter.key();

            DigitLineEdit* lineEdit = iter.value();
            if (lineEdit)
            {
                lineEdit->setFormat(3, 2);
                lineEdit->setValue(highLimits.paraValue(key3));
            }
        }
    } while (0);
}

void RefRangeSetupDialog::onSpeciesComboBoxCurrentIndexChanged(int index)
{
    qDebug() << "RefRangeSetupDialog onSpeciesComboBoxCurrentIndexChanged" << index;

    // 默认第一个参考组
    QString key1 = this->keys1.at(index);
    this->keys2 = Cache::refRangeKeys2(key1);

    // 下拉框选项
    ui.cbGroup->clear();
    foreach (QString key2, this->keys2)
    {
        ui.cbGroup->addItem(this->getString(key2));
    }

    // 默认第一个物种类型第一个参考组
    this->onGroupComboBoxCurrentIndexChanged(0);
}