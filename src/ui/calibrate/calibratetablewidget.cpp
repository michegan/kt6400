#include "paras.h"
#include "calibratetablewidget.h"


CalibrateTableWidget::CalibrateTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    this->setRows(9);
    this->setColumns(6);

    // У׼����
    this->paraNames = Paras::calibrateParaNames();

    // ������ͷ
    this->vHeadText << "Assay" << "1" << "2" << "3" << "4" << "5" << "Mean" << "CV%" << "Factor%";
}

CalibrateTableWidget::~CalibrateTableWidget()
{

}

// �������
void CalibrateTableWidget::setContent(const QList<ParaList>& contents)
{
    this->contents = contents;

    // ˢ��
    this->update();
}

// ��ȡ��ͷ����
QStringList CalibrateTableWidget::headText() const
{
    QStringList heads;

    heads.append("");
    heads.append(this->paraNames);

    return heads;
}

// ��ȡ�������
int CalibrateTableWidget::numOfItems()
{
    return this->rows();
}

QStringList CalibrateTableWidget::rowText(int row) const
{
    QStringList rowText;

    if (row < this->vHeadText.length())
    {
        rowText.append(this->vHeadText.at(row));
    }

    if (row < this->contents.length())
    {
        // this->vHeadText << "Assay" << "1" << "2" << "3" << "4" << "5" << "Mean"
        ParaList paraList = this->contents.at(row);

        foreach (QString paraName, this->paraNames)
        {
            Para para = paraList.para(paraName);
            if (PARA_NORMAL_FLAG == para.flag)
            {
                rowText.append(QString("%1").arg(para.value));
            }
            else
            {
                rowText.append(QString());
            }
        }
    }

    return rowText;
}