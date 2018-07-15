#include "field.h"
#include "messagebox.h"
#include "uivariants.h"
#include "ljqcfilewin.h"
#include "ljqclistwin.h"
#include "ljqcfiletable.h"
#include "ljqcsampletable.h"
#include "ljqctablewidget.h"


LJQcListWin::LJQcListWin(QWidget* parent)
    : FuncWin(parent), fileNo(0), from(0), lbFileNo(0), leFileNo(0), fileTable(new LJQcFileTable()), 
      sampleTable(0), tableWidget(new LJQcTableWidget(this))
{
    ui.setupUi(this);

    // 文件号
    this->fileNo = UIVariants::intVariant(F_FILENO);

    // 样本表
    this->sampleTable = new LJQcSampleTable(this->fileNo);
    this->allSamples = this->sampleTable->allSamples();

    // 创建状态条
    this->createStatusBar();

    // 窗口标识
    this->setWId("LJQcListWin");

    // 文件表格
    this->tableWidget->setLJQcSampleTable(this->sampleTable);
    this->tableWidget->setGeometry(10, 90, 780, 460);

    // 质控文件信息
    LJQcInfo ljQcInfo;
    ParaList lowLimits;
    ParaList highLimits;

    if (this->fileTable->getFile(this->fileNo, ljQcInfo, lowLimits, highLimits))
    {
        // 批号
        ui.leLotNo->setText(ljQcInfo.lotNo);

        // 有效期
        ui.leExpDate->setDate(ljQcInfo.expTime.date());
    }

    // 显示当前页
    int samples = this->allSamples.length();
    int columns = this->tableWidget->columns();

    this->from = (columns < samples ? samples - columns : 0);

    this->onSelectSampleChanged(this->sampleTable->selectedRecords());

    // 关联信号槽
    this->connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(onBtnBackClicked()));
    this->connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    this->connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    this->connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));

    this->connect(this->tableWidget, SIGNAL(columnClicked(int, bool)), this, SLOT(onColumnClicked(int, bool)));
    this->connect(this->sampleTable, SIGNAL(selectedRecordsChanged(const QList<int>&)), this, SLOT(onSelectSampleChanged(const QList<int>&)));
}

LJQcListWin::~LJQcListWin()
{
    // 文件表
    delete this->fileTable;
    // 样本表
    delete this->sampleTable;
}

// 创建状态条
void LJQcListWin::createStatusBar()
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

// 按钮点击
void LJQcListWin::onBtnBackClicked()
{
    this->switchToFuncWin(new LJQcFileWin());
}

void LJQcListWin::onBtnPrintClicked()
{

}

void LJQcListWin::onBtnDeleteClicked()
{
    if (QMessageBox::Yes == MessageBox::question(this, "Delete samples ?"))
    {
        // 删除选中样本
        this->sampleTable->deleteSelectSamples();
    }
}

void LJQcListWin::onBtnPageUpClicked()
{
    int columns = this->tableWidget->columns();

    // 页起始
    int samples = this->allSamples.length();
    if (this->from + columns * 2 < samples)
    {
        this->from += columns;
    }
    else
    {
        this->from = samples - columns;
    }

    // 显示当前页
    this->showCurrentPage();
}

void LJQcListWin::onBtnPageDownClicked()
{
    int columns = this->tableWidget->columns();

    // 页起始
    if (columns < this->from)
    {
        this->from -= columns;
    }
    else
    {
        this->from = 0;
    }

    // 显示当前页
    this->showCurrentPage();
}

// 表格列选中
void LJQcListWin::onColumnClicked(int columnNo, bool selected)
{
    int index = this->from + columnNo;
    if (0 <= index && index < this->allSamples.length())
    {
        int fid = this->allSamples.at(index);
        if (0 < fid)
        {
            // 新的当前样本
            this->sampleTable->selectedRecord(fid, selected);
        }
    }
}

// 选中样本变化
void LJQcListWin::onSelectSampleChanged(const QList<int>& fids)
{
    // 显示当前页
    this->showCurrentPage();
}

// 显示当前页
void LJQcListWin::showCurrentPage()
{
    int columns = this->tableWidget->columns();
    QList<int> selectSamples = this->sampleTable->selectedRecords();

    // 当前页
    for (int column = 0; column < columns; column++)
    {
        int index = this->from + column;
        if (0 <= index && index < this->allSamples.length())
        {
            int fid = this->allSamples.at(index);
            this->tableWidget->setSelect(column, selectSamples.contains(fid));
        }
    }
    this->tableWidget->setSamples(this->allSamples.mid(this->from, columns));

    // 按钮状态
    ui.pbPageDown->setEnabled(0 < this->from);
    ui.pbPageUp->setEnabled(this->from + columns < this->allSamples.length());
}