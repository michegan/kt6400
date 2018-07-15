#include <QtDebug>

#include "cache.h"
#include "countfuncwin.h"
#include "modeeditdialog.h"
#include "nextsampletable.h"
#include "specieseditdialog.h"


CountFuncWin::CountFuncWin(QWidget* parent)
    : FuncWin(parent), nextSampleInfo(new SampleInfo()), nextSampleTable(new NextSampleTable())
{
    // 窗口标识
    this->setWId("CountFuncWin");

    // 创建状态条
    this->createStatusBar();

    // 物种模式按钮，仅动物机型可见
    this->pbNextSpecies->setVisible(Cache::isForPets());

    // 获取下一样本信息
    this->nextSampleTable->nextSampleInfo(*this->nextSampleInfo);

    // 关联信号槽
    connect(this->pbNextSpecies, SIGNAL(clicked()), this, SLOT(onBtnSpeciesClcked()));
    connect(this->pbNextSampleMode, SIGNAL(clicked()), this, SLOT(onBtnModeClicked()));
}

CountFuncWin::~CountFuncWin()
{
    // 下一样本信息
    delete this->nextSampleInfo;

    // 下一样本数据表
    delete this->nextSampleTable;
}

// 下一样本信息
SampleInfo CountFuncWin::getNextSampleInfo() const
{
    return *this->nextSampleInfo;
}

void CountFuncWin::setNextSampleInfo(const SampleInfo& sampleInfo)
{
    // 样本信息
    if (this->nextSampleTable->setNextSampleInfo(sampleInfo))
    {
        *this->nextSampleInfo = sampleInfo;

        // 显示下一样本信息
        this->showNextSampleInfo(sampleInfo);
    }
    else
    {
        qWarning() << "CountFuncWin setNextSampleInfo setNextSampleInfo fail";
    }
}

// 创建状态条
void CountFuncWin::createStatusBar()
{
    // 基类处理
    FuncWin::createStatusBar();

    // 子类处理
    this->pbNextSpecies = new QPushButton(this);
    this->pbNextSpecies->setFlat(true);
    this->pbNextSpecies->setGeometry(320, 565, 40, 32);
    this->pbNextSpecies->setStyleSheet("margin: 1px; border: 1px; padding: 1px;");

    this->pbNextSampleMode = new QPushButton(this);
    this->pbNextSampleMode->setFlat(true);
    this->pbNextSampleMode->setGeometry(360, 565, 120, 32);
}

// 界面使能
void CountFuncWin::enableWindow(bool enable)
{
    // 基类处理
    FuncWin::enableWindow(enable);

    // 子类处理
    this->pbNextSpecies->setEnabled(enable);
    this->pbNextSampleMode->setEnabled(enable);
}

// 显示下一样本信息
void CountFuncWin::showNextSampleInfo(const SampleInfo& sampleInfo)
{
    QIcon icon;
    icon.addFile("./image/" + sampleInfo.modes.speciesImage(), QSize(32, 32));
    this->pbNextSpecies->setIcon(icon);
    this->pbNextSpecies->setWindowOpacity(0);

    this->setText(this->pbNextSampleMode, sampleInfo.modes.ids());
}

// 按钮点击
void CountFuncWin::onBtnModeClicked()
{
    // 下一样本信息
    SampleInfo* sampleInfo = this->nextSampleInfo;

    // 模式对话框
    ModeEditDialog dialog(this);
    dialog.setModes(sampleInfo->modes);

    if (QDialog::Accepted == dialog.exec())
    {
        // 从对话框获取模式信息
        sampleInfo->modes = dialog.getModes();

        // 更新数据库
        if (this->nextSampleTable->setNextSampleInfo(*sampleInfo))
        {
            this->showNextSampleInfo(*sampleInfo);
        }
        else
        {
            qWarning() << "CountFuncWin onBtnModeClicked setNextSampleInfo fail";
        }
    }
}

void CountFuncWin::onBtnSpeciesClcked()
{
    // 下一样本信息
    SampleInfo* sampleInfo = this->nextSampleInfo;

    // 模式对话框
    SpeciesEditDialog dialog(this);
    dialog.setSpeciesMode(sampleInfo->modes.speciesMode);

    if (QDialog::Accepted == dialog.exec())
    {
        // 从对话框获取模式信息
        sampleInfo->modes.speciesMode = dialog.speciesMode();

        // 更新数据库
        if (this->nextSampleTable->setNextSampleInfo(*sampleInfo))
        {
            this->showNextSampleInfo(*sampleInfo);
        }
        else
        {
            qWarning() << "CountFuncWin onBtnSpeciesClcked setNextSampleInfo fail";
        }
    }
}