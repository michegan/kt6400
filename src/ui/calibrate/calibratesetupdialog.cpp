#include <QtDebug>

#include "paraname.h"
#include "calibratesetupdialog.h"


CalibrateSetupDialog::CalibrateSetupDialog(QWidget* parent, Qt::WFlags flags)
    : SetupDialog(parent)
{
    ui.setupUi(this);

    // 界面字符串
    this->setWindowText();

    // 界面控件
    this->valueEdits.insert(PARA_WBC, ui.leWbc);
    this->valueEdits.insert(PARA_RBC, ui.leRbc);
    this->valueEdits.insert(PARA_PLT, ui.lePlt);
    this->valueEdits.insert(PARA_HGB, ui.leHgb);
    this->valueEdits.insert(PARA_MCV, ui.leMcv);

    // 关联信号槽
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

CalibrateSetupDialog::~CalibrateSetupDialog()
{

}

// 校准信息（批号）
QString CalibrateSetupDialog::lotNo() const
{
    return this->slotNo;
}

void CalibrateSetupDialog::setLotNo(const QString& lotNo)
{
    ui.leLotNo->setText(lotNo);
}

// 校准信息（靶值，含所有校准参数，通过FLAG区分）
// PARA_IGNORE_FLAG：不校准此参数；PARA_NORMAL_FLAG：校准此参数；
ParaList CalibrateSetupDialog::targets() const
{
    return this->stargets;
}

void CalibrateSetupDialog::setTargets(const ParaList& targets)
{
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->valueEdits.begin(); iter != this->valueEdits.end(); iter++)
    {
        QString key = iter.key();
        DigitLineEdit* lineEdit = this->valueEdits.value(key);

        if (0 <= targets.indexOfPara(key))
        {
            Para para = targets.para(key);
            if (PARA_NORMAL_FLAG == para.flag)
            {
                lineEdit->setValue(para.value);
            }
            else
            {
                lineEdit->clear();
            }
        }
        else
        {
            lineEdit->clear();
        }
    }
}

// 界面字符串
void CalibrateSetupDialog::setWindowText()
{
    // 基类处理
    Dialog::setWindowText();

    // 子类处理
    ui.leWbc->setText(PARA_WBC);
    ui.leRbc->setText(PARA_WBC);
    ui.lePlt->setText(PARA_WBC);
    ui.leHgb->setText(PARA_WBC);
    ui.leMcv->setText(PARA_WBC);

    this->setText(ui.lbLotNo, "IDS_LOT_NO");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// 从界面获取设置信息
void CalibrateSetupDialog::getSetupInfoFromUI()
{
    // 校准信息（批号）
    this->slotNo = ui.leLotNo->text();
    
    // 校准信息（靶值，含所有校准参数，通过FLAG区分）
    // PARA_IGNORE_FLAG：不校准此参数；PARA_NORMAL_FLAG：校准此参数且有效；PARA_ALARM_FLAG：校准此参数但有效；
    this->stargets.clear();
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->valueEdits.begin(); iter != this->valueEdits.end(); iter++)
    {
        QString key = iter.key();
        DigitLineEdit* lineEdit = this->valueEdits.value(key);

        if (lineEdit->isValid())
        {
            float value = lineEdit->value();
            if (0 < value)
            {
                this->stargets.appendPara(key, lineEdit->value());
            }
            else
            {
                this->stargets.appendPara(key, lineEdit->value(), PARA_IGNORE_FLAG);
            }
        }
        else
        {
            this->stargets.appendPara(key, lineEdit->value(), PARA_ALARM_FLAG);
        }
    }
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString CalibrateSetupDialog::isSetupInfoValid()
{
    foreach (Para para, this->stargets)
    {
        if (PARA_ALARM_FLAG == para.flag)
        {
            return para.name;
        }
    }
    return QString();
}

// 设置信息无效处理（提示信息）
QString CalibrateSetupDialog::onSetupInfoInvalidText(const QString& ret)
{
    return ("Invalid para");
}

QWidget* CalibrateSetupDialog::onSetupInfoInvalidWidget(const QString& ret)
{
    return this->valueEdits.value(ret, 0);
}

// 设置信息有效处理（保存设置信息）
bool CalibrateSetupDialog::onSetupInfoValid()
{
    return true;
}