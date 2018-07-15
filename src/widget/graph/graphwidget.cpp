#include <QPainter>
#include <QPainterPath>

#include "graphwidget.h"


class GraphWidgetPrivate
{
public:
    GraphWidgetPrivate();
    ~GraphWidgetPrivate();

public:
    // ����
    QString title;

    // X����Ϣ
    float xstep;
    float xminimum;
    float xmaximum;
    QString xname;

    // Y����Ϣ
    float ystep;
    float yminimum;
    float ymaximum;
    QString yname;

    // �߾�
    float marginLeft;
    float marginRight;
    float marginTop;
    float marginBottom;

    // ������ɫ
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

// ����
void GraphWidget::setTitle(const QString& title)
{
    d->title = title;
}

// ����������
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

// ������̶�
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

// �߾�
void GraphWidget::setMargin(float left, float right, float top, float bottom)
{
    d->marginLeft = left;
    d->marginRight = right;
    d->marginTop = top;
    d->marginBottom = bottom;
}

// ������ɫ
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

// �����¼�
void GraphWidget::paintEvent(QPaintEvent* event)
{
    // ���Ʊ���
    this->drawBackground();

    // ����������
    this->drawAxis();

    // ����ͼ��
    this->drawGraph();

    // ���Ʊ���
    this->drawTitle();
}

// ���ݾ���
QRect GraphWidget::content()
{
    int x = d->marginLeft;
    int y = d->marginTop;
    int width = (this->width() - d->marginLeft - d->marginRight);
    int height = (this->height() - d->marginTop - d->marginBottom);

    return QRect(x, y, qMax<int>(width, 0), qMax<int>(height, 0));
}

// �̶ȵ�
float GraphWidget::scaleX(float x)
{
    return x;
}

float GraphWidget::scaleY(float y)
{
    return y;
}

// ����������
void GraphWidget::drawAxis()
{
    QPainter painter(this);
    QRect content = this->content();

    // ����
    QPen pen(d->colorAxis);
    painter.setPen(pen);

    // X��
    painter.drawLine(content.bottomLeft(), content.bottomRight());
    painter.drawText(QRect(content.right(), content.bottom() - d->marginBottom / 2, d->marginRight, d->marginBottom), Qt::AlignCenter, d->xname);

    // Y��
    painter.drawLine(content.bottomLeft(), content.topLeft());
    painter.drawText(QRect(0, 0, d->marginLeft, d->marginTop), Qt::AlignCenter, d->yname);
}

// ���Ʊ���
void GraphWidget::drawTitle()
{
    QPainter painter(this);

    // ����
    QPen pen(d->colorTitle);
    painter.setPen(pen);

    // ���Ʊ���
    QRect content(0, 0, this->width(), d->marginTop);
    painter.drawText(content, Qt::AlignCenter, d->title);
}

// ���Ʊ���
void GraphWidget::drawBackground()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // ���Ʊ���
    QBrush brush(d->colorBackground);
    painter.fillRect(rect, brush);
}