#include <QPainter>

#include "paras.h"
#include "datetime.h"
#include "ljqcsampletable.h"
#include "ljqctablewidget.h"


LJQcTableWidget::LJQcTableWidget(QWidget* parent)
    : TableWidget(TableWidget::ColumnMode, parent), sampleTable(0)
{
    this->setRows(15);
    this->setColumns(8);
}

LJQcTableWidget::~LJQcTableWidget()
{

}

// 设置当前页样本
void LJQcTableWidget::setSamples(const QList<int>& samples)
{
    // 当前页样本
    this->samples.clear();

    for (int i = 0; i < samples.length() && i < this->columns(); i++)
    {
        this->samples.append(samples.at(i));
    }

    // 刷新
    this->update();
}

// 样本表
void LJQcTableWidget::setLJQcSampleTable(LJQcSampleTable* sampleTable)
{
    // 样本表
    this->sampleTable = sampleTable;
}

// 获取表头内容
QStringList LJQcTableWidget::headText() const
{
    QStringList heads;

    heads << "" << "DATE" << "TIME";
    heads.append(Paras::qcParaNames());

    return heads;
}

// 获取表格内容
int LJQcTableWidget::numOfItems()
{
    return this->samples.length();
}

QStringList LJQcTableWidget::columnText(int columnNo)
{
    QStringList columnText;

    // 样本列
    if (columnNo < this->samples.length())
    {
        // 取样本信息
        ParaList paraResult;
        SampleInfo sampleInfo;

        int fid = this->samples.at(columnNo);
        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // 样本信息
            columnText.append(QString::number(fid));
            columnText.append(sampleInfo.name);
            columnText.append(DateTime::dateToStringC(sampleInfo.testTime.date()));
            columnText.append(DateTime::timeToStringC(sampleInfo.testTime.time()));

            // 参数结果
            QStringList names = Paras::reportParaNames();
            foreach (QString name, names)
            {
                Para para = paraResult.para(name);
                columnText.append(para.valueToString(2));
            }
        }
    }

    return columnText;
}