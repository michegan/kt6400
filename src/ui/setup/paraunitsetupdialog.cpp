#include <QtDebug>

#include "paras.h"
#include "languagexml.h"
#include "paraunitxml.h"
#include "paraunitsxml.h"
#include "paraunitsetupdialog.h"


ParaUnitSetupDialog::ParaUnitSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // 参数结果控件
    this->wbcUnitWidget = new UnitWidget(this);
    this->wbcUnitWidget->setParas(Paras::wbcReportParaNames());
    this->wbcUnitWidget->setGeometry(10, 60, 200, 270);

    this->rbcUnitWidget = new UnitWidget(this);
    this->rbcUnitWidget->setParas(Paras::rbcReportParaNames());
    this->rbcUnitWidget->setGeometry(220, 60, 200, 270);

    this->pltUnitWidget = new UnitWidget(this);
    this->pltUnitWidget->setParas(Paras::pltReportParaNames());
    this->pltUnitWidget->setGeometry(430, 60, 200, 270);

    // 单位制（更改前）
    LanguageXml xml1;
    if (xml1.load())
    {
        this->unit1 = xml1.getTextValue2(KEY1_LANGUAGE, KEY2_CUR_UNIT);
        this->unit2 = this->unit1;
    }
    else
    {
        qWarning() << "ParaUnitSetupDialog ParaUnitSetupDialog load fail";
    }
    
    // 参数配置
    ParaUnitXml xml2;
    if (xml2.load())
    {
        QStringList keys1 = xml2.keys1();
        ui.cbGroup->addItems(keys1);

        // 下拉框当前选项变
        int index = keys1.indexOf(this->unit1);
        ui.cbGroup->setCurrentIndex(index);

        this->onComboBoxCurrentIndexChanged(this->unit1);
    }
    else
    {
        qWarning() << "ParaUnitSetupDialog ParaUnitSetupDialog load fail";
    }

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
    connect(ui.cbGroup, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxCurrentIndexChanged(const QString&)));
}

ParaUnitSetupDialog::~ParaUnitSetupDialog()
{

}

// 从界面获取设置信息
void ParaUnitSetupDialog::getSetupInfoFromUI()
{
    this->unit2 = ui.cbGroup->currentText();
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString ParaUnitSetupDialog::isSetupInfoValid()
{
    return QString();
}

// 设置信息无效处理（提示信息）
QString ParaUnitSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* ParaUnitSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// 设置信息有效处理（保存设置信息）
bool ParaUnitSetupDialog::onSetupInfoValid()
{
    LanguageXml xml;

    bool ret = xml.load();
    if (ret)
    {
        xml.setTextValue2(KEY1_LANGUAGE, KEY2_CUR_UNIT, this->unit2);
        ret = xml.save();
    }

    return ret;
}

// 下拉框当前选项变化
void ParaUnitSetupDialog::onComboBoxCurrentIndexChanged(const QString& text)
{
    qDebug() << "ParaUnitSetupDialog onComboBoxCurrentIndexChanged" << text;

    // 参考组配置
    ParaUnitXml xml;
    if (xml.load())
    {
        QString key1 = text;

        // WBC系
        ParaList paraList;
        QStringList names = Paras::wbcReportParaNames();

        foreach (QString name, names)
        {
            QString unit = xml.getTextValue2(key1, name);
            paraList.appendPara(name, 0, PARA_NORMAL_FLAG, unit);
        }
        this->wbcUnitWidget->setParaList(paraList);

        // RBC系
        paraList.clear();
        names = Paras::rbcReportParaNames();

        foreach (QString name, names)
        {
            QString unit = xml.getTextValue2(key1, name);
            paraList.appendPara(name, 0, PARA_NORMAL_FLAG, unit);
        }
        this->rbcUnitWidget->setParaList(paraList);

        // PLT系
        paraList.clear();
        names = Paras::pltReportParaNames();

        foreach (QString name, names)
        {
            QString unit = xml.getTextValue2(key1, name);
            paraList.appendPara(name, 0, PARA_NORMAL_FLAG, unit);
        }
        this->pltUnitWidget->setParaList(paraList);
    }
    else
    {
        qWarning() << "ParaUnitSetupDialog onComboBoxCurrentIndexChanged load fail";
    }
}