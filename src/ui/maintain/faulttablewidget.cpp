#include "language.h"
#include "faulttablewidget.h"


FaultTableWidget::FaultTableWidget(QWidget* parent)
    : TableWidget(TableWidget::RowMode, parent)
{
    this->setRows(10);
    this->setColumns(1);

    // ��������
    this->faultIds << "IDS_WBC_CLOG" << "IDS_RBC_CLOG" << "IDS_WBC_BUBBLE" << "IDS_HGB_BUBBLE" << "IDS_HGB_ERROR" << "IDS_MOTOR_H" << "IDS_MOTOR_V" 
                   << "IDS_SYRINGE_1" << "IDS_SYRINGE_2" << "IDS_NO_LYSE" << "IDS_NO_DILUENT" << "IDS_WASTE_FULL" << "IDS_BACKGROUND" << "IDS_NO_PAPER";
}

FaultTableWidget::~FaultTableWidget()
{

}

// �����б�
void FaultTableWidget::setFaults(const QList<int>& faults)
{
    this->faults = faults;
    this->setRows(faults.length());
}

// ��ȡ��ͷ����
QStringList FaultTableWidget::headText() const
{
    QStringList heads;

    heads.append("IDS_FAULT");

    return heads;
}

// ��ȡ�������
int FaultTableWidget::numOfItems()
{
    return this->rows();
}

QStringList FaultTableWidget::rowText(int row) const
{
    QStringList rowText;

    if (0 <= row && row < this->faults.length())
    {
        // ����
        int fault = this->faults.at(row);

        QString ids = this->faultIds.at(fault);
        rowText.append(Language::getString(ids.at(fault)));
    }

    return rowText;
}