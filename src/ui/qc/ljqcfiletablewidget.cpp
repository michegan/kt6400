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

// �ļ���
void LJQcFileTableWidget::setLJQcFileTable(LJQcFileTable* fileTable)
{
    this->fileTable = fileTable;

    // �ļ���������
    int files = fileTable->numOfRecords();
    this->setRows(files);
}

// ��ȡ��ͷ����
QStringList LJQcFileTableWidget::headText() const
{
    QStringList heads;

    heads << "FILENO" << "MODE" << "LOTNO" << "EXPDATE" << "SAMPLES";

    return heads;
}

// ��ȡ�������
int LJQcFileTableWidget::numOfItems()
{
    return this->rows();
}

QStringList LJQcFileTableWidget::rowText(int row) const
{
    QStringList rowText;

    // ȡ�ļ���Ϣ
    int fileNo = row + 1;

    LJQcInfo qcInfo;
    ParaList lowLimits;
    ParaList highLimits;

    if (this->fileTable && this->fileTable->getFile(fileNo, qcInfo, lowLimits, highLimits))
    {
        // �ļ���Ϣ
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

    // ȡ������Ϣ
    LJQcSampleTable sampleTable(fileNo);

    int samples = sampleTable.numOfRecords();
    rowText.append(QString::number(samples));

    return rowText;
}