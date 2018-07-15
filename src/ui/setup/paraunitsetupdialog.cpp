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

    // ��������ؼ�
    this->wbcUnitWidget = new UnitWidget(this);
    this->wbcUnitWidget->setParas(Paras::wbcReportParaNames());
    this->wbcUnitWidget->setGeometry(10, 60, 200, 270);

    this->rbcUnitWidget = new UnitWidget(this);
    this->rbcUnitWidget->setParas(Paras::rbcReportParaNames());
    this->rbcUnitWidget->setGeometry(220, 60, 200, 270);

    this->pltUnitWidget = new UnitWidget(this);
    this->pltUnitWidget->setParas(Paras::pltReportParaNames());
    this->pltUnitWidget->setGeometry(430, 60, 200, 270);

    // ��λ�ƣ�����ǰ��
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
    
    // ��������
    ParaUnitXml xml2;
    if (xml2.load())
    {
        QStringList keys1 = xml2.keys1();
        ui.cbGroup->addItems(keys1);

        // ������ǰѡ���
        int index = keys1.indexOf(this->unit1);
        ui.cbGroup->setCurrentIndex(index);

        this->onComboBoxCurrentIndexChanged(this->unit1);
    }
    else
    {
        qWarning() << "ParaUnitSetupDialog ParaUnitSetupDialog load fail";
    }

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
    connect(ui.cbGroup, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxCurrentIndexChanged(const QString&)));
}

ParaUnitSetupDialog::~ParaUnitSetupDialog()
{

}

// �ӽ����ȡ������Ϣ
void ParaUnitSetupDialog::getSetupInfoFromUI()
{
    this->unit2 = ui.cbGroup->currentText();
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString ParaUnitSetupDialog::isSetupInfoValid()
{
    return QString();
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString ParaUnitSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return QString();
}

QWidget* ParaUnitSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return 0;
}

// ������Ϣ��Ч��������������Ϣ��
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

// ������ǰѡ��仯
void ParaUnitSetupDialog::onComboBoxCurrentIndexChanged(const QString& text)
{
    qDebug() << "ParaUnitSetupDialog onComboBoxCurrentIndexChanged" << text;

    // �ο�������
    ParaUnitXml xml;
    if (xml.load())
    {
        QString key1 = text;

        // WBCϵ
        ParaList paraList;
        QStringList names = Paras::wbcReportParaNames();

        foreach (QString name, names)
        {
            QString unit = xml.getTextValue2(key1, name);
            paraList.appendPara(name, 0, PARA_NORMAL_FLAG, unit);
        }
        this->wbcUnitWidget->setParaList(paraList);

        // RBCϵ
        paraList.clear();
        names = Paras::rbcReportParaNames();

        foreach (QString name, names)
        {
            QString unit = xml.getTextValue2(key1, name);
            paraList.appendPara(name, 0, PARA_NORMAL_FLAG, unit);
        }
        this->rbcUnitWidget->setParaList(paraList);

        // PLTϵ
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