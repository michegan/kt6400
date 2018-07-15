#include <QFont>
#include <QPainter>

#include "unitwidget.h"


// 行高
#define HEAD_HEIGHT                  (38)
#define CONTENT_HEIGHT               (29)


UnitWidget::UnitWidget(QWidget* parent)
    : ParaWidget(parent)
{

}

UnitWidget::~UnitWidget()
{

}

// 绘制内容
void UnitWidget::drawContent()
{
    QPainter painter(this);
    QFont font = painter.font();

    // 每列的比例（4列，两侧边距预留4%）
    const int NumOfColumns = 2;
    float scales[NumOfColumns] = { 0.52f, 0.4f };

    // 表头
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

    // 内容
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