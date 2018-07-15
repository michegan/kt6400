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

// ���õ�ǰҳ����
void LJQcTableWidget::setSamples(const QList<int>& samples)
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
void LJQcTableWidget::setLJQcSampleTable(LJQcSampleTable* sampleTable)
{
    // ������
    this->sampleTable = sampleTable;
}

// ��ȡ��ͷ����
QStringList LJQcTableWidget::headText() const
{
    QStringList heads;

    heads << "" << "DATE" << "TIME";
    heads.append(Paras::qcParaNames());

    return heads;
}

// ��ȡ�������
int LJQcTableWidget::numOfItems()
{
    return this->samples.length();
}

QStringList LJQcTableWidget::columnText(int columnNo)
{
    QStringList columnText;

    // ������
    if (columnNo < this->samples.length())
    {
        // ȡ������Ϣ
        ParaList paraResult;
        SampleInfo sampleInfo;

        int fid = this->samples.at(columnNo);
        if (this->sampleTable->getSample(fid, sampleInfo, paraResult))
        {
            // ������Ϣ
            columnText.append(QString::number(fid));
            columnText.append(sampleInfo.name);
            columnText.append(DateTime::dateToStringC(sampleInfo.testTime.date()));
            columnText.append(DateTime::timeToStringC(sampleInfo.testTime.time()));

            // �������
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