#include "field.h"
#include "paras.h"
#include "paraname.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqcsetupwin.h"
#include "ljqcfiletable.h"


LJQcSetupWin::LJQcSetupWin(QWidget* parent)
    : SetupFuncWin(parent), fileNo(0), lbFileNo(0), leFileNo(0), fileTable(new LJQcFileTable())
{
    ui.setupUi(this);

    // 默认焦点
    ui.leLotNo->setFocus();

    // 文件号
    this->fileNo = UIVariants::intVariant(F_FILENO);

    // 创建状态条
    this->createStatusBar();

    // 窗口标识
    this->setWId("LJQcSetupWin");

    // 编辑框
    this->lowEdits.insert(PARA_WBC, ui.leWbcLow);
    this->lowEdits.insert(PARA_LYM_PER, ui.leLymPerLow);
    this->lowEdits.insert(PARA_GRAN_PER, ui.leGranPerLow);
    this->lowEdits.insert(PARA_LYM_NUM, ui.leLymNumLow);
    this->lowEdits.insert(PARA_GRAN_NUM, ui.leGranNumLow);
    this->lowEdits.insert(PARA_RBC, ui.leRbcLow);
    this->lowEdits.insert(PARA_HGB, ui.leHgbLow);
    this->lowEdits.insert(PARA_HCT, ui.leHctLow);
    this->lowEdits.insert(PARA_MCH, ui.leMchLow);
    this->lowEdits.insert(PARA_MCV, ui.leMcvLow);
    this->lowEdits.insert(PARA_MCHC, ui.leMchcLow);
    this->lowEdits.insert(PARA_PLT, ui.lePltLow);

    this->highEdits.insert(PARA_WBC, ui.leWbcHigh);
    this->highEdits.insert(PARA_LYM_PER, ui.leLymPerHigh);
    this->highEdits.insert(PARA_GRAN_PER, ui.leGranPerHigh);
    this->highEdits.insert(PARA_LYM_NUM, ui.leLymNumHigh);
    this->highEdits.insert(PARA_GRAN_NUM, ui.leGranNumHigh);
    this->highEdits.insert(PARA_RBC, ui.leRbcHigh);
    this->highEdits.insert(PARA_HGB, ui.leHgbHigh);
    this->highEdits.insert(PARA_HCT, ui.leHctHigh);
    this->highEdits.insert(PARA_MCH, ui.leMchHigh);
    this->highEdits.insert(PARA_MCV, ui.leMcvHigh);
    this->highEdits.insert(PARA_MCHC, ui.leMchcHigh);
    this->highEdits.insert(PARA_PLT, ui.lePltHigh);

    // 质控文件信息
    if (this->fileTable->getFile(this->fileNo, this->ljQcInfoPre, this->lowLimitsPre, this->highLimitsPre))
    {
        this->ljQcInfoPost = this->ljQcInfoPre;
        this->lowLimitsPost = this->lowLimitsPre;
        this->highLimitsPost = this->highLimitsPre;

        if (this->ljQcInfoPre.isSetted())
        {
            // 批号
            ui.leLotNo->setText(this->ljQcInfoPre.lotNo);

            // 有效期
            ui.leExpDate->setDate(this->ljQcInfoPre.expTime.date());

            // 参考范围下限
            for (QMap<QString, DigitLineEdit*>::iterator iter = this->lowEdits.begin(); iter != this->lowEdits.end(); iter++)
            {
                DigitLineEdit* lineEdit = iter.value();
                if (lineEdit)
                {
                    lineEdit->setFormat(3, 2);
                    lineEdit->setValue(lowLimitsPre.paraValue(iter.key()));
                }
            }

            // 参考范围上限
            for (QMap<QString, DigitLineEdit*>::iterator iter = this->highEdits.begin(); iter != this->highEdits.end(); iter++)
            {
                DigitLineEdit* lineEdit = iter.value();
                if (lineEdit)
                {
                    lineEdit->setFormat(3, 2);
                    lineEdit->setValue(highLimitsPre.paraValue(iter.key()));
                }
            }
        }
        else
        {
            // 参考范围下限
            for (QMap<QString, DigitLineEdit*>::iterator iter = this->lowEdits.begin(); iter != this->lowEdits.end(); iter++)
            {
                DigitLineEdit* lineEdit = iter.value();
                if (lineEdit)
                {
                    lineEdit->clear();
                }
            }

            // 参考范围上限
            for (QMap<QString, DigitLineEdit*>::iterator iter = this->highEdits.begin(); iter != this->highEdits.end(); iter++)
            {
                DigitLineEdit* lineEdit = iter.value();
                if (lineEdit)
                {
                    lineEdit->clear();
                }
            }
        }
       
    }

    // 关联信号槽
    this->connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(onBtnBackClicked()));
}

LJQcSetupWin::~LJQcSetupWin()
{
    // 文件表
    delete this->fileTable;
}

// 创建状态条
void LJQcSetupWin::createStatusBar()
{
    // 基类处理
    FuncWin::createStatusBar();

    // 子类处理
    this->lbFileNo = new QLabel(this);
    this->lbFileNo->setText("File No.");
    this->lbFileNo->setGeometry(0, 565, 120, 30);

    this->leFileNo = new QLabel(this);
    this->leFileNo->setText(LJQcInfo::fileDesc(this->fileNo));
    this->leFileNo->setGeometry(120, 565, 240, 30);
}

// 从界面获取设置信息
void LJQcSetupWin::getSetupInfoFromUI()
{
    // 批号
    this->ljQcInfoPost.lotNo = ui.leLotNo->text();

    // 有效期
    this->ljQcInfoPost.expTime = QDateTime(ui.leExpDate->date(), QTime());

    // 上下限
    ParaList lowLimits;
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->lowEdits.begin(); iter != this->lowEdits.end(); iter++)
    {
        DigitLineEdit* lineEdit = iter.value();
        if (lineEdit)
        {
            this->lowLimitsPost.setParaValue(iter.key(), lineEdit->value());
        }
    }

    // 参考范围上限（修改后）
    ParaList highLimits;
    for (QMap<QString, DigitLineEdit*>::iterator iter = this->highEdits.begin(); iter != this->highEdits.end(); iter++)
    {
        DigitLineEdit* lineEdit = iter.value();
        if (lineEdit)
        {
            this->highLimitsPost.setParaValue(iter.key(), lineEdit->value());
        }
    }
}

// 设置信息是否变化
bool LJQcSetupWin::isSetupInfoChanged()
{
    QStringList paras = Paras::qcParaNames();
    foreach (QString para, paras)
    {
        float value1 = this->lowLimitsPre.paraValue(para);
        float value2 = this->lowLimitsPost.paraValue(para);

        float value3 = this->highLimitsPre.paraValue(para);
        float value4 = this->highLimitsPost.paraValue(para);

        if ((value1 != value2) || (value3 != value4))
        {
            return true;
        }
    }

    return ((this->ljQcInfoPost.lotNo != this->ljQcInfoPre.lotNo) || (this->ljQcInfoPost.expTime != this->ljQcInfoPre.expTime));
}

// 设置信息有效性检测（有效返回0，无效返回对应错误码）
QString LJQcSetupWin::isSetupInfoValid()
{
    if (this->ljQcInfoPost.lotNo.isEmpty())
    {
        return "Lot No.";
    }
    else if (this->ljQcInfoPost.expTime.isNull())
    {
        return "Exp. Date";
    }
    else
    {
        foreach (Para para, this->lowLimitsPost)
        {
            float low = para.value;
            float high = this->highLimitsPost.paraValue(para.name);

            if (low < high)
            {
                return para.name;
            }
        }
        return QString();
    }
}

// 设置信息无效处理（提示信息）
QString LJQcSetupWin::onSetupInfoInvalidText(const QString& ret)
{
    return (ret + " invalid");
}

QWidget* LJQcSetupWin::onSetupInfoInvalidWidget(const QString& ret)
{
    if ("Lot No." == ret)
    {
        return ui.leLotNo;
    }
    else if ("Exp. Date" == ret)
    {
       return  ui.leExpDate;
    }
    else
    {
        return this->lowEdits.value(ret, 0);
    }
}

// 设置信息有效处理（保存设置信息）
bool LJQcSetupWin::onSetupInfoValid()
{
    return this->fileTable->updateFile(this->fileNo, this->ljQcInfoPost, this->lowLimitsPost, this->highLimitsPost);
}

// 按钮点击
void LJQcSetupWin::onBtnBackClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}