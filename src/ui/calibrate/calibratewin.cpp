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

    // ���ڱ�ʶ
    this->setWId("CalibrateWin");

    // ����״̬��
    this->createStatusBar();

    // �����ַ���
    this->setWindowText();

    // У׼���
    this->tableWidget->setEnabled(false);
    this->tableWidget->setGeometry(20, 110, 760, 400);

    // ��ʾУ׼������Ϣ
    this->showCalibrateInfo(this->lotNo);
    // ��ʾУ׼�����Ϣ
    this->showCalibrateResult(this->targets, this->results);

    // ��һ������Ϣ
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();
    this->showNextSampleInfo(nextSampleInfo);

    // �����źŲ�
    connect(ui.pbClear, SIGNAL(clicked()), this, SLOT(onBtnClearClicked()));
    connect(ui.pbSetup, SIGNAL(clicked()), this, SLOT(onBtnSetupClicked()));

    connect(this->count, SIGNAL(algFinished()), this, SLOT(onCountAlgFinished()));
    connect(this->count, SIGNAL(countFinished(bool)), this, SLOT(onCountFinished(bool)));
}

CalibrateWin::~CalibrateWin()
{
    // ��������
    delete this->count;
}

// ����������
void CalibrateWin::onAbsorbKeyDown()
{
    qDebug() << "CalibrateWin onAbsorbKeyDown";

    // ��һ������Ϣ
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

    // ��������
    const SampleInfo nextSampleInfo = this->getNextSampleInfo();

    int ret = this->count->startCount(nextSampleInfo);
    if (EXIT_OK == ret)
    {
        // ����ʹ��
        this->enableWindow(false);
        // ������ʹ��
        this->enableAbsorbKey(false);
    }
    else
    {
        // ��������ʱ��ʧ��
        this->onRunTimeseqFail(ret);
    }
}

// �����ַ���
void CalibrateWin::setWindowText()
{
    // ���ദ��
    CountFuncWin::setWindowText();

    // ���ദ��
    this->setText(ui.pbClear, "IDS_CLEAR");
    this->setText(ui.pbSetup, "IDS_SETUP");
    this->setText(ui.lbLotNo, "IDS_LOT_NO");
}

// ����״̬��
void CalibrateWin::createStatusBar()
{
    // ���ദ��CountFuncWin���Ѿ����ù��������������Σ�
    // CountFuncWin::createStatusBar();

    // ���ദ��
}

// ����ʹ��
void CalibrateWin::enableWindow(bool enable)
{
    // ���ദ��
    CountFuncWin::enableWindow(enable);

    // ���ദ��
    ui.pbClear->setEnabled(enable);
    ui.pbSetup->setEnabled(enable);
}

// �л������ܴ���
void CalibrateWin::switchToFuncWin(FuncWin* funcWin)
{
    if (this->isCalibrateFinished())
    {
        if (QMessageBox::Yes == MessageBox::question(this, "Save results?"))
        {
            // ����У׼ϵ��
            if (this->isCalibrateOk())
            {
                // ����У׼���
                if (this->saveCalibrateResult())
                {
                    // �л�����
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
                    // �л�����
                    CountFuncWin::switchToFuncWin(funcWin);
                }
            }
        }
    }
    else if (this->isCalibrating())
    {
        if (QMessageBox::Yes == MessageBox::question(this, "Result will lose, go on?"))
        {
            // �л�����
            CountFuncWin::switchToFuncWin(funcWin);
        }
    }
    else
    {
        // �л�����
        CountFuncWin::switchToFuncWin(funcWin);
    }
}

// ��ť���
void CalibrateWin::onBtnClearClicked()
{
    // ��ռ������
    this->results.clear();

    // ��ʾУ׼�����Ϣ
    this->showCalibrateResult(this->targets, this->results);
}

void CalibrateWin::onBtnSetupClicked()
{
    // У׼���ý���
    CalibrateSetupDialog dialog(this);
    dialog.setLotNo(this->lotNo);
    dialog.setTargets(this->targets);

    if (QDialog::Accepted == dialog.exec())
    {
        this->lotNo = dialog.lotNo();
        this->targets = dialog.targets();

        // ��ʾУ׼������Ϣ
        this->showCalibrateInfo(this->lotNo);
        // ��ʾУ׼�����Ϣ
        this->showCalibrateResult(this->targets, this->results);
    }
}

// �㷨����
void CalibrateWin::onCountAlgFinished()
{
    ParaList results = this->count->paraResult();

    // ���������Ч�Լ��
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
        // ����������
        this->results.append(result);

        // ��ʾУ׼�����Ϣ
        this->showCalibrateResult(this->targets, this->results);
    }
}

// ��������
void CalibrateWin::onCountFinished(bool result)
{
    // ����ʹ��
    this->enableWindow(true);
    // ������ʹ��
    this->enableAbsorbKey(true);
}

// �Ƿ�У׼��
bool CalibrateWin::isCalibrating() const
{
    return (!this->results.isEmpty());
}

// �Ƿ�У׼ͨ��
bool CalibrateWin::isCalibrateOk() const
{
    foreach (Para para, this->cvs)
    {
        // ����ϵ�����ܳ���5%
        if (0.05 < para.value)
        {
            return false;
        }
    }
    return true;
}


// �Ƿ�У׼����
bool CalibrateWin::isCalibrateSetted() const
{
    foreach (Para para, this->targets)
    {
        // ֻҪ��һ���������ã����϶�Ϊ�����ã�δ���ñ�ǣ�PARA_IGNORE_FLAG��
        if (PARA_NORMAL_FLAG == para.flag)
        {
            return true;
        }
    }
    return false;
}

// �Ƿ�У׼����
bool CalibrateWin::isCalibrateFinished() const
{
    return (5 <= this->results.length());
}

// ����У׼���
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

// ��ʾУ׼������Ϣ
void CalibrateWin::showCalibrateInfo(const QString& lotNo)
{
    ui.leLotNo->setText(lotNo);
}

// ��ʾУ׼�����Ϣ
void CalibrateWin::showCalibrateResult(const ParaList& targets, const QList<ParaList>& results)
{
    QList<ParaList> contents;

    // ��ֵ
    contents.append(targets);

    // �������
    contents.append(results);

    // ͳ�ƽ����"Mean" << "CV%" << "Factor%"��
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