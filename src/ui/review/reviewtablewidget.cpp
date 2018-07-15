#include <QtDebug>

#include "paras.h"
#include "uicolor.h"
#include "datetime.h"
#include "refrange.h"
#include "reviewsampletable.h"
#include "reviewtablewidget.h"


ReviewTableWidget::ReviewTableWidget(QWidget* parent)
    : TableWidget(TableWidget::ColumnMode, parent), from(0), sampleTable(0)
{
    this->setRows(25);
    this->setColumns(8);
}

ReviewTableWidget::~ReviewTableWidget()
{

}

// 设置起始索引
void ReviewTableWidget::setFrom(int from)
{
    this->from = from;

    // 刷新
    this->update();
}

// 设置当前页样本
void ReviewTableWidget::setSamples(const QList<int>& samples)
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
void ReviewTableWidget::setReviewSampleTable(ReviewSampleTable* sampleTable)
{
    // 样本表
    this->sampleTable = sampleTable;
}

// 选中模式（默认单选）
bool ReviewTableWidget::isSingleSelect() const
{
    return false;
}

// 获取表头内容
QStringList ReviewTableWidget::headText() const
{
    QStringList heads;

    heads << "" << "ID" << "NAME" << "DATE" << "TIME";
    heads.append(Paras::reportParaNames());

    return heads;
}

// 获取表格内容
int ReviewTableWidget::numOfItems()
{
    return this->samples.length();
}

QStringList ReviewTableWidget::columnText(int column)
{
    QStringList columnText;

    // 样本列
    if (column < this->samples.length())
    {
        // 取样本信息
        ParaList paraResult;
        SampleInfo sampleInfo;

        int fid = this->samples.at(column);
        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // 对应参考范围
            ParaList lowLimits;
            ParaList highLimits;
            if (RefRange::getLimits(sampleInfo, lowLimits, highLimits))
            {
                paraResult.setLimits(lowLimits, highLimits);
            }
            else
            {
                qWarning() << "ReviewTableWidget columnText getLimits fail";
            }

            // 样本信息
            columnText.append(QString::number(this->from + column + 1));
            columnText.append(sampleInfo.sampleId);
            columnText.append(sampleInfo.name);
            columnText.append(DateTime::dateToStringC(sampleInfo.testTime.date()));
            columnText.append(DateTime::timeToStringC(sampleInfo.testTime.time()));

            // 参数结果
            QStringList names = Paras::reportParaNames();
            for (int row = 0; row < names.length(); row++)
            {
                QString name = names.at(row);
                Para para = paraResult.para(name);

                // 有报警的参数，特定前景色显示
                QColor color = UIColor::paraColor(para);
                this->setColor(row + 5, column, color);

                // 有高低报警的参数，出显示结果外，还需要显示高低报警标识）
                QString text = para.valueToString(2);
                if (PARA_H_FLAG == para.flag || PARA_L_FLAG == para.flag)
                {
                    text += (" " + para.flagToString());
                }
                columnText.append(text);
            }
        }
    }

    return columnText;
}