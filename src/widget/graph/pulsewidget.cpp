#include <QPainter>
#include <QPainterPath>

#include "pulsewidget.h"


PulseWidget::PulseWidget(QWidget* parent)
    : GraphWidget(parent), showGrid(true)
{
    // 标题
    this->setTitle("Pulse");

    // 颜色
    this->setColor(Qt::green);

    // 边距
    this->setMargin(40, 20, 20, 20);
}

PulseWidget::~PulseWidget()
{

}

// 清空直方图
void PulseWidget::clear()
{
    // 清空数据
    this->datas.clear();
    this->lines.clear();

    // 刷新界面
    this->update();
}

// 显示选项
void PulseWidget::setShowGrid(bool showGrid)
{
    this->showGrid = showGrid;
}

// 绘制图形
void PulseWidget::drawGraph()
{
    // 绘制背景线
    if (this->showGrid)
    {
        this->drawGrid();
    }

    // 绘制曲线
    if (!this->datas.isEmpty())
    {
        this->drawCurve();
    }

    // 绘制分类线
    if (!this->lines.isEmpty())
    {
        this->drawLine();
    }

    // 绘制刻度值
    this->drawScale();
}

// 刻度点
float PulseWidget::scaleX(float x)
{
    QRect content = this->content();
    float scale = 1.0 * content.width() / (this->xmaximum() - this->xminimum());

    return (content.left() + (x - this->xminimum()) * scale);
}

float PulseWidget::scaleY(float y)
{
    QRect content = this->content();
    float scale = 1.0 * content.height() / (this->ymaximum() - this->yminimum());

    return (content.bottom() - (y - this->yminimum()) * scale);
}

// 图像点
float PulseWidget::graphX(float x)
{
    QRect content = this->content();
    float scale = 1.0 * content.width() / (this->xmaximum() - this->xminimum());

    return (content.left() + x * scale);
}

float PulseWidget::graphY(float y)
{
    QRect content = this->content();
    float scale = 1.0 * content.height() / (this->ymaximum() - this->yminimum());

    return (content.bottom() - (y - this->yminimum()) * scale);
}

// 绘制曲线
void PulseWidget::drawCurve()
{
    QPainterPath path;
    QPainter painter(this);
    QRect content = this->content();

    // 坐标原点
    path.moveTo(content.left(), content.bottom());

    // 直方图
    for (int i = 0; i < this->datas.length(); i++)
    {
        float data = this->datas.at(i);

        float px = this->graphX(i);
        float py = qMax<float>(content.top(), this->graphY(data));

        path.lineTo(px, py);
    }

    // 绘制直方图
    QPen pen(this->colorGraph());
    painter.setPen(pen);
    painter.drawPath(path);
}

// 绘制背景线
void PulseWidget::drawGrid()
{
    QPainter painter(this);
    QRect content = this->content();

    // 画笔
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(this->colorAxis());

    painter.setPen(pen);

    // X轴
    for (float step = this->xminimum(); step <= this->xmaximum(); step += this->xstep())
    {
        float px = this->scaleX(step);

        painter.drawLine(px, content.bottom(), px, content.top());
    }

    // Y轴
    for (float step = this->yminimum(); step <= this->ymaximum(); step += this->ystep())
    {
        float py = this->scaleY(step);

        painter.drawLine(content.left(), py, content.right(), py);
    }
}

// 绘制分类线
void PulseWidget::drawLine()
{
    QPainter painter(this);
    QRect content = this->content();

    // 画笔
    painter.setPen(this->colorAxis());

    // 分类线
    for (int i = 0; i < this->lines.length(); i++)
    {
        int px = this->graphX(this->lines.at(i));

        painter.drawLine(px, content.bottom(), px, content.top());
    }
}

// 绘制刻度值
void PulseWidget::drawScale()
{
    QPainter painter(this);
    QRect content = this->content();

    // 画笔
    painter.setPen(this->colorAxis());

    // X轴
    for (float step = this->xminimum(); step <= this->xmaximum(); step += this->xstep())
    {
        float px =  this->scaleX(step);

        // 刻度线
        painter.drawLine(px, content.bottom(), px, content.bottom() + 5);

        // 刻度值
        QString text = QString::number(step + this->xminimum(), 'f', 0);
        painter.drawText(QRect(px - 30, content.bottom() + 5, 60, 15), Qt::AlignCenter, text);
    }

    // Y轴
    for (float step = this->yminimum(); step <= this->ymaximum(); step += this->ystep())
    {
        float py = this->scaleY(step);

        // 刻度线
        painter.drawLine(content.left() - 5, py, content.left(), py);

        // 刻度值
        QString text = QString::number(step + this->yminimum(), 'f', 0);
        painter.drawText(QRect(0, py - 5, content.left(), 10), Qt::AlignCenter, text);
    }
}

// 设置图形数据
void PulseWidget::setDataF(const QList<float>& datas)
{
    // 填充数据
    this->datas = datas;

    // 刷新界面
    this->update();
}

// 设置分类线数据
void PulseWidget::setLineF(const QList<float>& lines)
{
    // 填充数据
    this->lines = lines;

    // 刷新界面
    this->update();
}