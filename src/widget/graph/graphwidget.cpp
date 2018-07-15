#include <QPainter>
#include <QPainterPath>

#include "graphwidget.h"


class GraphWidgetPrivate
{
public:
    GraphWidgetPrivate();
    ~GraphWidgetPrivate();

public:
    // 标题
    QString title;

    // X轴信息
    float xstep;
    float xminimum;
    float xmaximum;
    QString xname;

    // Y轴信息
    float ystep;
    float yminimum;
    float ymaximum;
    QString yname;

    // 边距
    float marginLeft;
    float marginRight;
    float marginTop;
    float marginBottom;

    // 绘制颜色
    QColor colorName;
    QColor colorAxis;
    QColor colorTitle;
    QColor colorGraph;
    QColor colorBackground;
};


GraphWidgetPrivate::GraphWidgetPrivate()
    : title("GRAPH"),  xstep(20), xminimum(0), xmaximum(100), xname(""), ystep(20), yminimum(0), ymaximum(100), yname(""), 
      marginLeft(20), marginRight(20), marginTop(20), marginBottom(20), 
      colorName(Qt::white), colorAxis(Qt::white), colorTitle(Qt::white), colorGraph(Qt::white), colorBackground(Qt::black)
{

}

GraphWidgetPrivate::~GraphWidgetPrivate()
{

}


GraphWidget::GraphWidget(QWidget* parent)
    : QWidget(parent), d(new GraphWidgetPrivate())
{

}

GraphWidget::~GraphWidget()
{
    delete d;
}

// 标题
void GraphWidget::setTitle(const QString& title)
{
    d->title = title;
}

// 坐标轴名称
QString GraphWidget::xname() const
{
    return d->xname;
}

QString GraphWidget::yname() const
{
    return d->yname;
}

void GraphWidget::setName(const QString& xname, const QString& yname)
{
    d->xname = xname;
    d->yname = yname;
}

// 坐标轴刻度
float GraphWidget::xstep() const
{
    return d->xstep;
}

float GraphWidget::xminimum() const
{
    return d->xminimum;
}
;
float GraphWidget::xmaximum() const
{
    return d->xmaximum;
}

void GraphWidget::setXAxis(float minimum, float maximum, float step)
{
    d->xstep = step;
    d->xminimum = minimum;
    d->xmaximum = maximum;
}

float GraphWidget::ystep() const
{
    return d->ystep;
}

float GraphWidget::yminimum() const
{
    return d->yminimum;
}

float GraphWidget::ymaximum() const
{
    return d->ymaximum;
}

void GraphWidget::setYAxis(float minimum, float maximum, float step)
{
    d->ystep = step;
    d->yminimum = minimum;
    d->ymaximum = maximum;
}

// 边距
void GraphWidget::setMargin(float left, float right, float top, float bottom)
{
    d->marginLeft = left;
    d->marginRight = right;
    d->marginTop = top;
    d->marginBottom = bottom;
}

// 设置颜色
QColor GraphWidget::colorAxis() const
{
    return d->colorAxis;
}

QColor GraphWidget::colorGraph() const
{
    return d->colorGraph;
}

void GraphWidget::setColor(const QColor& graph)
{
    d->colorGraph = graph;
}

void GraphWidget::setColor(const QColor& background, const QColor& title, const QColor& graph, const QColor& axis)
{
    d->colorAxis = axis;
    d->colorGraph = graph;
    d->colorTitle = title;
    d->colorBackground = background;
}

// 绘制事件
void GraphWidget::paintEvent(QPaintEvent* event)
{
    // 绘制背景
    this->drawBackground();

    // 绘制坐标轴
    this->drawAxis();

    // 绘制图形
    this->drawGraph();

    // 绘制标题
    this->drawTitle();
}

// 内容矩形
QRect GraphWidget::content()
{
    int x = d->marginLeft;
    int y = d->marginTop;
    int width = (this->width() - d->marginLeft - d->marginRight);
    int height = (this->height() - d->marginTop - d->marginBottom);

    return QRect(x, y, qMax<int>(width, 0), qMax<int>(height, 0));
}

// 刻度点
float GraphWidget::scaleX(float x)
{
    return x;
}

float GraphWidget::scaleY(float y)
{
    return y;
}

// 绘制坐标轴
void GraphWidget::drawAxis()
{
    QPainter painter(this);
    QRect content = this->content();

    // 画笔
    QPen pen(d->colorAxis);
    painter.setPen(pen);

    // X轴
    painter.drawLine(content.bottomLeft(), content.bottomRight());
    painter.drawText(QRect(content.right(), content.bottom() - d->marginBottom / 2, d->marginRight, d->marginBottom), Qt::AlignCenter, d->xname);

    // Y轴
    painter.drawLine(content.bottomLeft(), content.topLeft());
    painter.drawText(QRect(0, 0, d->marginLeft, d->marginTop), Qt::AlignCenter, d->yname);
}

// 绘制标题
void GraphWidget::drawTitle()
{
    QPainter painter(this);

    // 画笔
    QPen pen(d->colorTitle);
    painter.setPen(pen);

    // 绘制标题
    QRect content(0, 0, this->width(), d->marginTop);
    painter.drawText(content, Qt::AlignCenter, d->title);
}

// 绘制背景
void GraphWidget::drawBackground()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // 绘制背景
    QBrush brush(d->colorBackground);
    painter.fillRect(rect, brush);
}