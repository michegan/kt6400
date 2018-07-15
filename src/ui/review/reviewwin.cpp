#include <QtDebug>

#include "field.h"
#include "refrange.h"
#include "transmit.h"
#include "reviewwin.h"
#include "messagebox.h"
#include "reviewsampletable.h"
#include "reviewtablewidget.h"
#include "reviewdeletedialog.h"
#include "reviewsearchdialog.h"


ReviewWin::ReviewWin(QWidget* parent)
    : FuncWin(parent), from(0), lbPos(0), lbSelected(0), sampleTable(ReviewSampleTable::instance()), tableWidget(new ReviewTableWidget(this))
{
    ui.setupUi(this);

    // 窗口标识
    this->setWId("ReviewWin");

    // 创建状态条
    this->createStatusBar();

    // 界面字符串
    this->setWindowText();

    // 列表
    this->tableWidget->setGeometry(2, 45, 796, 515);
    this->tableWidget->setReviewSampleTable(this->sampleTable);

    // 显示当前页
    this->onDataChanged();

    // 关联信号槽
    this->connect(ui.pbSearch, SIGNAL(clicked()), this, SLOT(onBtnSearchClicked()));
    this->connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    this->connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(onBtnPrintClicked()));
    this->connect(ui.pbPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(ui.pbPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
    this->connect(ui.pbTransmit, SIGNAL(clicked()), this, SLOT(onBtnTransmitClicked()));

    this->connect(this->tableWidget, SIGNAL(columnClicked(int, bool)), this, SLOT(onColumnClicked(int, bool)));

    this->connect(this->sampleTable, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));
    this->connect(this->sampleTable, SIGNAL(selectedRecordsChanged(const QList<int>&)), this, SLOT(onSelectSampleChanged(const QList<int>&)));
    this->connect(this->sampleTable, SIGNAL(currentSampleChanged(int, const QList<int>&)), this, SLOT(onCurrentSampleChanged(int, const QList<int>&)));
}

ReviewWin::~ReviewWin()
{

}

// 界面字符串
void ReviewWin::setWindowText()
{
    // 基类处理
    FuncWin::setWindowText();

    // 子类处理
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbTransmit, "IDS_TRANSMIT");
    this->setText(ui.pbPrint, "IDS_PRINT");
    this->setText(ui.pbSearch, "IDS_SEARCH");
    this->setText(ui.pbPageDown, "IDS_PAGE_DOWN");
    this->setText(ui.pbPageUp, "IDS_PAGE_UP");

    this->setText(this->lbPos, "IDS_POS");
    this->setText(this->lbSelected, "IDS_SELECTED");
}

// 创建状态条
void ReviewWin::createStatusBar()
{
    // 基类处理
    FuncWin::createStatusBar();

    // 子类处理
    this->lbPos = new QLabel(this);
    this->lbPos->setGeometry(0, 565, 240, 32);

    this->lbSelected = new QLabel(this);
    this->lbSelected->setGeometry(240, 565, 240, 32);
}

// 按钮点
void ReviewWin::onBtnSearchClicked()
{
    ReviewSearchDialog dialog(this);
    dialog.exec();

    QString condition = dialog.condition();
    qDebug() << "ReviewWin onBtnSearchClicked" << condition;

    this->sampleTable->clearConditions();
    if (!condition.isEmpty())
    {
        this->sampleTable->addWhereCondition(condition);
    }
    this->sampleTable->selectSamples();
}

void ReviewWin::onBtnDeleteClicked()
{
    ReviewDeleteDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        bool deleteAll = dialog.isDeleteAll();
        if (deleteAll)
        {
            // 删除全部样本（不带条件即删除全部）
            this->sampleTable->deleteAllSamples();
        }
        else
        {
            // 删除选中样本
            this->sampleTable->deleteSelectSamples();
        }
    }
}

void ReviewWin::onBtnPrintClicked()
{

}

void ReviewWin::onBtnPageUpClicked()
{
    int columns = this->tableWidget->columns();
    QList<int> allSamples = this->sampleTable->allSamples();

    // 页起始
    if (this->from + columns * 2 < allSamples.length())
    {
        this->from += columns;
    }
    else
    {
        this->from = allSamples.length() - columns;
    }

    // 显示当前页
    this->showCurrentPage();
}

void ReviewWin::onBtnPageDownClicked()
{
    int columns = this->tableWidget->columns();
    QList<int> allSamples = this->sampleTable->allSamples();

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

void ReviewWin::onBtnTransmitClicked()
{
    // 参数检查
    if (0 == this->sampleTable)
    {
        qWarning() << "ReviewWin onBtnTransmitClicked no sampleTable";
        return;
    }

    // 缓存选中样本
    QList<int> selectSamples = this->sampleTable->selectedRecords();
    if (selectSamples.isEmpty())
    {
        qDebug() << "ReviewWin onBtnTransmitClicked no selectedRecords";
        return;
    }

    // 逐个通信
    int sended = 0;
    foreach (int fid, selectSamples)
    {
        // 获取样本
        HistInfo wbcHist;
        HistInfo rbcHist;
        HistInfo pltHist;
        ParaList paraResult;
        SampleInfo sampleInfo;

        if (!this->sampleTable->getSample(fid, sampleInfo, paraResult) || !this->sampleTable->getSample(fid, wbcHist, rbcHist, pltHist))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked getSample" << fid;
            break;
        }

        // 对应参考范围
        ParaList lowLimits;
        ParaList highLimits;
        if (!RefRange::getLimits(sampleInfo, lowLimits, highLimits))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked no selectedRecords" << fid;
            break;
        }

        // 发送样本
        paraResult.setLimits(lowLimits, highLimits);
        if (!Transmit::sendSample(sampleInfo, paraResult, wbcHist, rbcHist, pltHist))
        {
            qWarning() << "ReviewWin onBtnTransmitClicked sendSample fail" << fid;
            break;
        }

        // 发送样本数+1
        sended++;
    }

    // 提示用户
    MessageBox::information(this, QString("Transmit %1 records of %2").arg(sended).arg(selectSamples.length()));
}

// 表格列选中
void ReviewWin::onColumnClicked(int columnNo, bool selected)
{
    int index = this->from + columnNo;

    int fid = this->sampleTable->fid(index);
    if (0 < fid)
    {
        // 新的当前样本
        this->sampleTable->setCurrentIndex(index);
        this->sampleTable->selectedRecord(fid, selected);
    }
}

// 数据变化
void ReviewWin::onDataChanged()
{
    int columns = this->tableWidget->columns();
    int current = this->sampleTable->currentIndex();

    this->from = (columns < current ? current - columns + 1 : 0);

    this->onSelectSampleChanged(this->sampleTable->selectedRecords());
    this->onCurrentSampleChanged(current, this->sampleTable->allSamples());
}

// 选中样本变化
void ReviewWin::onSelectSampleChanged(const QList<int>& fids)
{
    // 显示当前页
    this->showCurrentPage();
}

// 当前样本变化
void ReviewWin::onCurrentSampleChanged(int index, const QList<int>& fids)
{
    int from = this->from;
    int length = fids.length();
    int columns = this->tableWidget->columns();

    // 计算新的起始列（后续列足够，则不更改起始列）
    if (from + columns <= length)
    {
        this->from = from;
    }
    else
    {
        this->from = (columns < length ? length - columns : 0);
    }

    // 显示当前页
    this->showCurrentPage();
}

// 刷新状态栏
void ReviewWin::updateStatusBar()
{
    const int samples = sampleTable->allSamples().length();

    const int current = sampleTable->currentIndex() + 1;
    this->lbPos->setText(QString("%1 : %2 / %3").arg(this->getString("IDS_POS")).arg(current).arg(samples));

    const int selects = sampleTable->selectedRecords().length();
    this->lbSelected->setText(QString("%1 : %2").arg(this->getString("IDS_SELECTED")).arg(selects));
}

// 显示当前页
void ReviewWin::showCurrentPage()
{
    int columns = this->tableWidget->columns();
    int currentIndex = this->sampleTable->currentIndex();
    QList<int> allSamples = this->sampleTable->allSamples();
    QList<int> selectSamples = this->sampleTable->selectedRecords();

    // 当前页
    this->tableWidget->clearColors();

    for (int column = 0; column < columns; column++)
    {
        int fid = this->sampleTable->fid(this->from + column);
        this->tableWidget->setSelect(column, selectSamples.contains(fid));
    }

    this->tableWidget->setFrom(this->from);
    this->tableWidget->setCurrent(currentIndex - this->from);
    this->tableWidget->setSamples(allSamples.mid(this->from, columns));

    // 按钮状态
    ui.pbPageDown->setEnabled(0 < this->from);
    ui.pbPageUp->setEnabled(this->from + columns < allSamples.length());

    // 刷新状态栏
    this->updateStatusBar();
}