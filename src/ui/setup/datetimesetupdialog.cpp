#include "datetime.h"
#include "languagexml.h"
#include "datetimesetupdialog.h"


DateTimeSetupDialog::DateTimeSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);
    
    // ���ڸ�ʽ
    LanguageXml xml;
    if (xml.load())
    {
        this->dateFormat1 = xml.getTextValue2(KEY1_LANGUAGE, KEY2_DATE_FORMAT);
    }
    this->dateFormat2 = this->dateFormat1;

    // ���ڸ�ʽѡ��
    QStringList dateFormats;
    dateFormats << "yyyy-MM-dd" << "dd-MM-yyyy";

    ui.cbFormat->insertItems(0, dateFormats);

    int index = dateFormats.indexOf(this->dateFormat1);
    ui.cbFormat->setCurrentIndex(index);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(ui.cbFormat, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxCurrentIndexChanged(const QString&)));
}

DateTimeSetupDialog::~DateTimeSetupDialog()
{

}

// �ӽ����ȡ������Ϣ
void DateTimeSetupDialog::getSetupInfoFromUI()
{
    this->dateFormat2 = ui.cbFormat->currentText();
}

// ������Ϣ��Ч�Լ�⣨��Ч����0����Ч���ض�Ӧ�����룩
QString DateTimeSetupDialog::isSetupInfoValid()
{
    if (!ui.leDate->isValid())
    {
        return "DATE";
    }

    if (!ui.leTime->isValid())
    {
        return "TIME";
    }

    return "";
}

// ������Ϣ��Ч������ʾ��Ϣ��
QString DateTimeSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    if ("DATE" == ret)
    {
        return "Invalid date";
    }
    else if ("TIME" == ret)
    {
        return "Invalid time";
    }
    else
    {
        return QString();
    }
}

QWidget* DateTimeSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    if ("DATE" == ret)
    {
        return ui.leDate;
    }
    else if ("TIME" == ret)
    {
        return ui.leTime;
    }
    else
    {
        return 0;
    }
}

// ������Ϣ��Ч��������������Ϣ��
bool DateTimeSetupDialog::onSetupInfoValid()
{
    bool ret = false;

    LanguageXml xml;
    if (xml.load())
    {
        xml.setTextValue2(KEY1_LANGUAGE, KEY2_DATE_FORMAT, this->dateFormat2);
        if (xml.save())
        {
            // �������ڸ�ʽ
            DateTime::setDateFormat(this->dateFormat2);

            ret = true;
        }
    }

    return ret;
}

// ����ѡ��仯
void DateTimeSetupDialog::onComboBoxCurrentIndexChanged(const QString& text)
{
    ui.leDate->setDateFormat(text);
}

// ��ť���
void DateTimeSetupDialog::onBtnCancelClicked()
{
    // �ָ����ڸ�ʽ
    DateTime::setDateFormat(this->dateFormat1);

    // ���ദ��
    SetupDialog::onBtnCancelClicked();
}