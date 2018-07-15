#include <QFont>
#include <QPainter>
#include <QMouseEvent>

#include "reagent.h"
#include "reagentwidget.h"


// 边距
#define MARGIN              (3)


ReagentWidget::ReagentWidget(QWidget* parent)
    : QWidget(parent)
{

}

ReagentWidget::~ReagentWidget()
{

}

// 试剂颜色（正常态颜色，异常态统一红色）
void ReagentWidget::setColor(int reagent, const QColor& color)
{
    // 保存颜色
    if (this->colors.contains(reagent))
    {
        this->colors[reagent] = color;
    }
    else
    {
        this->colors.insert(reagent, color);
    }

    // 刷新
    this->update();
}

// 绘制事件
void ReagentWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect content = this->content();

    // 试剂列表
    QList<int> reagents = Reagent::reagents();
    int rows = reagents.length();

    // 行高列宽
    float rowHeight = (content.height() - (rows - 1) * MARGIN) / rows;

    // 绘制每种试剂
    float x = content.left();
    float y = content.top();

    for (int i = 0; i < reagents.length(); i++)
    {
        // 试剂状态决定颜色
        int reagent = reagents.at(i);

        Reagent::setRemain(reagent, 50);
        Reagent::setVolume(reagent, 130);

        QColor color = Qt::green;
        if (Reagent::isEmpty(reagent))
        {
            // 空
            color = QColor(243, 115, 112);
        }
        else if (Reagent::isEnough(reagent))
        {
            // 足够
            color = QColor(248, 225, 61);
        }
        else
        {
            // 不足
            color = QColor(170, 218, 20);
        }

        // 外边框
        painter.setPen(color);

        QRect rect = QRect(x, y, content.width(), rowHeight);
        painter.drawRoundedRect(rect, MARGIN, MARGIN);

        // 中边框
        // painter.setPen(QColor(8, 8, 6));

        // rect.adjust(1, 1, -1, -1);
        // painter.drawRoundedRect(rect, MARGIN, MARGIN);

        // 内边框
        rect.adjust(3, 3, -2, -2);

        if (Reagent::isEmpty(reagent))
        {
            painter.fillRect(rect, color);
        }
        else
        {
            float remain = Reagent::remain(reagent);
            float volume = Reagent::volume(reagent);

            rect.setWidth(rect.width() * remain / volume);

            painter.fillRect(rect, color);
        }

        y += (rowHeight + MARGIN);
    }
}

// 鼠标事件
void ReagentWidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    // 左键
    if (Qt::LeftButton == event->button())
    {
        // 内容矩形
        QRect rect = this->content();
        if (rect.contains(event->pos()))
        {
            // 获得焦点，并上报鼠标事件
            this->setFocus();

            emit clicked();
        }
    }
}

// 内容矩形
QRect ReagentWidget::content()
{
    int width = (this->width() - 2 * MARGIN);
    int height = (this->height() - 2 * MARGIN);

    return QRect(MARGIN, MARGIN, qMax<int>(width, 0), qMax<int>(height, 0));
}