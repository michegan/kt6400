#include <QtDebug>

#include "enum.h"
#include "cache.h"
#include "count.h"
#include "modes.h"
#include "paras.h"
#include "compute.h"
#include "messagebox.h"
#include "sampleinfo.h"
#include "calfactorxml.h"
#include "calibratewin.h"
#include "modeeditdialog.h"
#include "nextsampletable.h"
#include "calibratesetupdialog.h"
#include "calibratetablewidget.h"


CalibrateWin::CalibrateWin(QWidget* parent)
    : CountFuncWin(parent), count(new Count()), tableWidget(new CalibrateTableWidget(this))
{
    ui.setupUi(this);

    // 窗口标识
    this->setWId("CalibrateWin");

    // 创建状态条
    this->createStatusBar();

    // 界面字符串
    this->setWindowText();

    // 校准表格
    this->tableWidget->setEnabled(false);
    this->tableWidget->setGeometry(20, 110, 760, 400);

    // 显示校准设置信息
    this->showCalibrateInfo(this->lotNo);
    // 显示校准结果信息
    this->showCalibrateResult(this->targets, this->results);

    // 下一样本信息
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();
    this->showNextSampleInfo(nextSampleInfo);

    // 关联信号槽
    connect(ui.pbClear, SIGNAL(clicked()), this, SLOT(onBtnClearClicked()));
    connect(ui.pbSetup, SIGNAL(clicked()), this, SLOT(onBtnSetupClicked()));

    connect(this->count, SIGNAL(algFinished()), this, SLOT(onCountAlgFinished()));
    connect(this->count, SIGNAL(countFinished(bool)), this, SLOT(onCountFinished(bool)));
}

CalibrateWin::~CalibrateWin()
{
    // 计数服务
    delete this->count;
}

// 吸样键按下
void CalibrateWin::onAbsorbKeyDown()
{
    qDebug() << "CalibrateWin onAbsorbKeyDown";

    // 下一样本信息
    if (!this->isCalibrateSetted())
    {
        MessageBox::information(this, "Please set calibrate info first");
        return;
    }

    if (this->isCalibrateFinished())
    {
        MessageBox::information(this, "Calibrate finished");
        return;
    }

    // 启动计数
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();

    int ret = this->count->startCount(nextSampleInfo);
    if (EXIT_OK == ret)
    {
        // 界面使能
        this->enableWindow(false);
        // 吸样键使能
        this->enableAbsorbKey(false);
    }
    else
    {
        // 启动计数时序失败
        this->onRunTimeseqFail(ret);
    }
}

// 界面字符串
void CalibrateWin::setWindowText()
{
    // 基类处理
    CountFuncWin::setWindowText();

    // 子类处理
    this->setText(ui.pbClear, "IDS_CLEAR");
    this->setText(ui.pbSetup, "IDS_SETUP");
    this->setText(ui.lbLotNo, "IDS_LOT_NO");
}

// 创建状态条
void CalibrateWin::createStatusBar()
{
    // 基类处理（CountFuncWin中已经调用过，所以这里屏蔽）
    // CountFuncWin::createStatusBar();

    // 子类处理
}

// 界面使能
void CalibrateWin::enableWindow(bool enable)
{
    // 基类处理
    CountFuncWin::enableWindow(enable);

    // 子类处理
    ui.pbClear->setEnabled(enable);
    ui.pbSetup->setEnabled(enable);
}

// 切换到功能窗口
void CalibrateWin::switchToFuncWin(FuncWin* funcWin)
{
    if (this->isCalibrateFinished())
    {
        if (QMessageBox::Yes == MessageBox::question(this, "Save results?"))
        {
            // 保存校准系数
            if (this->isCalibrateOk())
            {
                // 保存校准结果
                if (this->saveCalibrateResult())
                {
                    // 切换窗口
                    CountFuncWin::switchToFuncWin(funcWin);
                }
                else
                {
                    MessageBox::information(this, "Save fail");
                }
            }
            else
            {
                if (QMessageBox::Yes == MessageBox::question(this, "Calibrate fail, exit?"))
                {
                    // 切换窗口
                    CountFuncWin::switchToFuncWin(funcWin);
                }
            }
        }
    }
    else if (this->isCalibrating())
    {
        if (QMessageBox::Yes == MessageBox::question(this, "Result will lose, go on?"))
        {
            // 切换窗口
            CountFuncWin::switchToFuncWin(funcWin);
        }
    }
    else
    {
        // 切换窗口
        CountFuncWin::switchToFuncWin(funcWin);
    }
}

// 按钮点击
void CalibrateWin::onBtnClearClicked()
{
    // 清空计数结果
    this->results.clear();

    // 显示校准结果信息
    this->showCalibrateResult(this->targets, this->results);
}

void CalibrateWin::onBtnSetupClicked()
{
    // 校准设置界面
    CalibrateSetupDialog dialog(this);
    dialog.setLotNo(this->lotNo);
    dialog.setTargets(this->targets);

    if (QDialog::Accepted == dialog.exec())
    {
        this->lotNo = dialog.lotNo();
        this->targets = dialog.targets();

        // 显示校准设置信息
        this->showCalibrateInfo(this->lotNo);
        // 显示校准结果信息
        this->showCalibrateResult(this->targets, this->results);
    }
}

// 算法结束
void CalibrateWin::onCountAlgFinished()
{
    ParaList results = this->count->paraResult();

    // 计数结果有效性检查
    ParaList result;
    foreach (Para target, this->targets)
    {
        Para para = results.para(target.name);
        if (PARA_NORMAL_FLAG == para.flag)
        {
            result.appendPara(target.name, para.value, target.flag);
        }
    }

    if (result.length() < this->targets.length())
    {
        MessageBox::information(this, "Invalid count result");
    }
    else
    {
        // 保存计数结果
        this->results.append(result);

        // 显示校准结果信息
        this->showCalibrateResult(this->targets, this->results);
    }
}

// 计数结束
void CalibrateWin::onCountFinished(bool result)
{
    // 界面使能
    this->enableWindow(true);
    // 吸样键使能
    this->enableAbsorbKey(true);
}

// 是否校准中
bool CalibrateWin::isCalibrating() const
{
    return (!this->results.isEmpty());
}

// 是否校准通过
bool CalibrateWin::isCalibrateOk() const
{
    foreach (Para para, this->cvs)
    {
        // 变异系数不能超过5%
        if (0.05 < para.value)
        {
            return false;
        }
    }
    return true;
}


// 是否校准设置
bool CalibrateWin::isCalibrateSetted() const
{
    foreach (Para para, this->targets)
    {
        // 只要有一个参数设置，则认定为已设置（未设置标记：PARA_IGNORE_FLAG）
        if (PARA_NORMAL_FLAG == para.flag)
        {
            return true;
        }
    }
    return false;
}

// 是否校准结束
bool CalibrateWin::isCalibrateFinished() const
{
    return (5 <= this->results.length());
}

// 保存校准结果
bool CalibrateWin::saveCalibrateResult()
{
    bool ret = false;

    CalFactorXml xml;
    if (xml.load())
    {
        foreach (Para factor, this->factors)
        {
            if (PARA_NORMAL_FLAG == factor.flag)
            {
                float value = xml.getFloatValue2(KEY1_USER, factor.name);
                xml.setFloatValue2(KEY1_USER, factor.name, value * factor.value);
            }
        }

        if (xml.save())
        {
            ret = true;
        }
    }

    return ret;
}

// 显示校准设置信息
void CalibrateWin::showCalibrateInfo(const QString& lotNo)
{
    ui.leLotNo->setText(lotNo);
}

// 显示校准结果信息
void CalibrateWin::showCalibrateResult(const ParaList& targets, const QList<ParaList>& results)
{
    QList<ParaList> contents;

    // 靶值
    contents.append(targets);

    // 计数结果
    contents.append(results);

    // 统计结果（"Mean" << "CV%" << "Factor%"）
    if (this->isCalibrateFinished())
    {
        ParaList means;
        ParaList cvs;
        ParaList factors;

        foreach (Para target, targets)
        {
            QString name = target.name;
            float* values = new float[results.length()];

            for (int i = 0; i < results.length(); i++)
            {
                ParaList result = results.at(i);
                *(values + i) = result.paraValue(name);
            }

            float mean = Compute::getMean<float>(values, results.length());
            float cv = Compute::getCv<float>(values, results.length());

            means.appendPara(name, mean, target.flag);
            cvs.appendPara(name, cv, target.flag);
            factors.appendPara(name, target.value / mean, target.flag);

            delete [] values;
        }

        contents.append(means);
        contents.append(cvs);
        contents.append(factors);

        this->cvs = cvs;
        this->factors = factors;
    }

    this->tableWidget->setContent(contents);
}