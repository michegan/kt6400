#include "datetime.h"
#include "language.h"
#include "ljqcfiletable.h"
#include "ljqcsampletable.h"
#include "ljqcfiletablewidget.h"


LJQcFileTableWidget::LJQcFileTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    this->setRows(0);
    this->setColumns(5);
}

LJQcFileTableWidget::~LJQcFileTableWidget()
{

}

// 文件表
void LJQcFileTableWidget::setLJQcFileTable(LJQcFileTable* fileTable)
{
    this->fileTable = fileTable;

    // 文件数即行数
    int files = fileTable->numOfRecords();
    this->setRows(files);
}

// 获取表头内容
QStringList LJQcFileTableWidget::headText() const
{
    QStringList heads;

    heads << "FILENO" << "MODE" << "LOTNO" << "EXPDATE" << "SAMPLES";

    return heads;
}

// 获取表格内容
int LJQcFileTableWidget::numOfItems()
{
    return this->rows();
}

QStringList LJQcFileTableWidget::rowText(int row) const
{
    QStringList rowText;

    // 取文件信息
    int fileNo = row + 1;

    LJQcInfo qcInfo;
    ParaList lowLimits;
    ParaList highLimits;

    if (this->fileTable && this->fileTable->getFile(fileNo, qcInfo, lowLimits, highLimits))
    {
        // 文件信息
        rowText.append(qcInfo.fileDesc());
        QString ids = qcInfo.modes.ids();
        rowText.append(Language::getString(ids));
        rowText.append(qcInfo.lotNo);
        rowText.append(DateTime::dateToStringC(qcInfo.expTime.date()));
    }
    else
    {
        rowText.append("");
        rowText.append("");
        rowText.append("");
        rowText.append("");
    }

    // 取样本信息
    LJQcSampleTable sampleTable(fileNo);

    int samples = sampleTable.numOfRecords();
    rowText.append(QString::number(samples));

    return rowText;
}