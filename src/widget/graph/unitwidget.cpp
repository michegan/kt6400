#include <QFont>
#include <QPainter>

#include "unitwidget.h"


// �и�
#define HEAD_HEIGHT                  (38)
#define CONTENT_HEIGHT               (29)


UnitWidget::UnitWidget(QWidget* parent)
    : ParaWidget(parent)
{

}

UnitWidget::~UnitWidget()
{

}

// ��������
void UnitWidget::drawContent()
{
    QPainter painter(this);
    QFont font = painter.font();

    // ÿ�еı�����4�У�����߾�Ԥ��4%��
    const int NumOfColumns = 2;
    float scales[NumOfColumns] = { 0.52f, 0.4f };

    // ��ͷ
    painter.setPen(this->foregroundHead);

    QString heads[NumOfColumns] = { "Name", "Unit" };

    float x = (this->width() * 0.02);
    for (int column = 0; column < NumOfColumns; column ++)
    {
        font.setBold(true);
        painter.setFont(font);

        int columtWidth = (this->width() * scales[column]);

        QRect rect(x, 0, columtWidth, HEAD_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, heads[column]);

        x = rect.right();
    }

    // ����
    painter.setPen(this->foregroundContent);

    for (int i = 0; i < this->paraList.length(); i++)
    {
        Para para = this->paraList.at(i);

        float x = (this->width() * 0.02);
        float y = (HEAD_HEIGHT + i * CONTENT_HEIGHT);

        // Name
        font.setBold(false);
        painter.setFont(font);

        float columtWidth = (this->width() * scales[0]);

        QRect rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, para.name);

        // Unit
        font.setBold(false);
        painter.setFont(font);

        x = rect.right();
        columtWidth = (this->width() * scales[1]);

        rect = QRect(x, y, columtWidth, CONTENT_HEIGHT);
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, para.unit);
    }
}