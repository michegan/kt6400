#include "datetime.h"
#include "languagexml.h"
#include "datetimesetupdialog.h"


DateTimeSetupDialog::DateTimeSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);
    
    // 日期格式
    LanguageXml xml;
    if (xml.load())
    {
        this->dateFormat1 = xml.getTextValue2(KEY1_LANGUAGE, KEY2_DATE_FORMAT);
    }
    this->dateFormat2 = this->dateFormat1;

    // 日期格式选项
    QStringList dateFormats;
    dateFormats << "yyyy-MM-dd" << "dd-MM-yyyy";

    ui.cbFormat->insertItems(0, dateFormats);

    int index = dateFormats.indexOf(this->dateFormat1);
    ui.cbFormat->setCurrentIndex(index);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(ui.cbFormat, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxCurrentIndexChanged(const QString&)));
}

DateTimeSetupDialog::~DateTimeSetupDialog()
{

}

// 从界面获取设置信息
void DateTimeSetupDialog::getSetupInfoFromUI()
{
    this->dateFormat2 = ui.cbFormat->currentText();
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
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

// 设置信息无效处理（提示信息）
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

// 设置信息有效处理（保存设置信息）
bool DateTimeSetupDialog::onSetupInfoValid()
{
    bool ret = false;

    LanguageXml xml;
    if (xml.load())
    {
        xml.setTextValue2(KEY1_LANGUAGE, KEY2_DATE_FORMAT, this->dateFormat2);
        if (xml.save())
        {
            // 保存日期格式
            DateTime::setDateFormat(this->dateFormat2);

            ret = true;
        }
    }

    return ret;
}

// 下拉选项变化
void DateTimeSetupDialog::onComboBoxCurrentIndexChanged(const QString& text)
{
    ui.leDate->setDateFormat(text);
}

// 按钮点击
void DateTimeSetupDialog::onBtnCancelClicked()
{
    // 恢复日期格式
    DateTime::setDateFormat(this->dateFormat1);

    // 基类处理
    SetupDialog::onBtnCancelClicked();
}