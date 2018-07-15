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

// ������ʼ����
void ReviewTableWidget::setFrom(int from)
{
    this->from = from;

    // ˢ��
    this->update();
}

// ���õ�ǰҳ����
void ReviewTableWidget::setSamples(const QList<int>& samples)
{
    // ��ǰҳ����
    this->samples.clear();

    for (int i = 0; i < samples.length() && i < this->columns(); i++)
    {
        this->samples.append(samples.at(i));
    }

    // ˢ��
    this->update();
}

// ������
void ReviewTableWidget::setReviewSampleTable(ReviewSampleTable* sampleTable)
{
    // ������
    this->sampleTable = sampleTable;
}

// ѡ��ģʽ��Ĭ�ϵ�ѡ��
bool ReviewTableWidget::isSingleSelect() const
{
    return false;
}

// ��ȡ��ͷ����
QStringList ReviewTableWidget::headText() const
{
    QStringList heads;

    heads << "" << "ID" << "NAME" << "DATE" << "TIME";
    heads.append(Paras::reportParaNames());

    return heads;
}

// ��ȡ�������
int ReviewTableWidget::numOfItems()
{
    return this->samples.length();
}

QStringList ReviewTableWidget::columnText(int column)
{
    QStringList columnText;

    // ������
    if (column < this->samples.length())
    {
        // ȡ������Ϣ
        ParaList paraResult;
        SampleInfo sampleInfo;

        int fid = this->samples.at(column);
        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // ��Ӧ�ο���Χ
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

            // ������Ϣ
            columnText.append(QString::number(this->from + column + 1));
            columnText.append(sampleInfo.sampleId);
            columnText.append(sampleInfo.name);
            columnText.append(DateTime::dateToStringC(sampleInfo.testTime.date()));
            columnText.append(DateTime::timeToStringC(sampleInfo.testTime.time()));

            // �������
            QStringList names = Paras::reportParaNames();
            for (int row = 0; row < names.length(); row++)
            {
                QString name = names.at(row);
                Para para = paraResult.para(name);

                // �б����Ĳ������ض�ǰ��ɫ��ʾ
                QColor color = UIColor::paraColor(para);
                this->setColor(row + 5, column, color);

                // �иߵͱ����Ĳ���������ʾ����⣬����Ҫ��ʾ�ߵͱ�����ʶ��
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