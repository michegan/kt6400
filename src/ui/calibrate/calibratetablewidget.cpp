#include "paras.h"
#include "calibratetablewidget.h"


CalibrateTableWidget::CalibrateTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    this->setRows(9);
    this->setColumns(6);

    // 校准参数
    this->paraNames = Paras::calibrateParaNames();

    // 首列列头
    this->vHeadText << "Assay" << "1" << "2" << "3" << "4" << "5" << "Mean" << "CV%" << "Factor%";
}

CalibrateTableWidget::~CalibrateTableWidget()
{

}

// 表格内容
void CalibrateTableWidget::setContent(const QList<ParaList>& contents)
{
    this->contents = contents;

    // 刷新
    this->update();
}

// 获取表头内容
QStringList CalibrateTableWidget::headText() const
{
    QStringList heads;

    heads.append("");
    heads.append(this->paraNames);

    return heads;
}

// 获取表格内容
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