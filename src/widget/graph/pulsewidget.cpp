#include <QPainter>
#include <QPainterPath>

#include "pulsewidget.h"


PulseWidget::PulseWidget(QWidget* parent)
    : GraphWidget(parent), showGrid(true)
{
    // ����
    this->setTitle("Pulse");

    // ��ɫ
    this->setColor(Qt::green);

    // �߾�
    this->setMargin(40, 20, 20, 20);
}

PulseWidget::~PulseWidget()
{

}

// ���ֱ��ͼ
void PulseWidget::clear()
{
    // �������
    this->datas.clear();
    this->lines.clear();

    // ˢ�½���
    this->update();
}

// ��ʾѡ��
void PulseWidget::setShowGrid(bool showGrid)
{
    this->showGrid = showGrid;
}

// ����ͼ��
void PulseWidget::drawGraph()
{
    // ���Ʊ�����
    if (this->showGrid)
    {
        this->drawGrid();
    }

    // ��������
    if (!this->datas.isEmpty())
    {
        this->drawCurve();
    }

    // ���Ʒ�����
    if (!this->lines.isEmpty())
    {
        this->drawLine();
    }

    // ���ƿ̶�ֵ
    this->drawScale();
}

// �̶ȵ�
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

// ͼ���
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

// ��������
void PulseWidget::drawCurve()
{
    QPainterPath path;
    QPainter painter(this);
    QRect content = this->content();

    // ����ԭ��
    path.moveTo(content.left(), content.bottom());

    // ֱ��ͼ
    for (int i = 0; i < this->datas.length(); i++)
    {
        float data = this->datas.at(i);

        float px = this->graphX(i);
        float py = qMax<float>(content.top(), this->graphY(data));

        path.lineTo(px, py);
    }

    // ����ֱ��ͼ
    QPen pen(this->colorGraph());
    painter.setPen(pen);
    painter.drawPath(path);
}

// ���Ʊ�����
void PulseWidget::drawGrid()
{
    QPainter painter(this);
    QRect content = this->content();

    // ����
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(this->colorAxis());

    painter.setPen(pen);

    // X��
    for (float step = this->xminimum(); step <= this->xmaximum(); step += this->xstep())
    {
        float px = this->scaleX(step);

        painter.drawLine(px, content.bottom(), px, content.top());
    }

    // Y��
    for (float step = this->yminimum(); step <= this->ymaximum(); step += this->ystep())
    {
        float py = this->scaleY(step);

        painter.drawLine(content.left(), py, content.right(), py);
    }
}

// ���Ʒ�����
void PulseWidget::drawLine()
{
    QPainter painter(this);
    QRect content = this->content();

    // ����
    painter.setPen(this->colorAxis());

    // ������
    for (int i = 0; i < this->lines.length(); i++)
    {
        int px = this->graphX(this->lines.at(i));

        painter.drawLine(px, content.bottom(), px, content.top());
    }
}

// ���ƿ̶�ֵ
void PulseWidget::drawScale()
{
    QPainter painter(this);
    QRect content = this->content();

    // ����
    painter.setPen(this->colorAxis());

    // X��
    for (float step = this->xminimum(); step <= this->xmaximum(); step += this->xstep())
    {
        float px =  this->scaleX(step);

        // �̶���
        painter.drawLine(px, content.bottom(), px, content.bottom() + 5);

        // �̶�ֵ
        QString text = QString::number(step + this->xminimum(), 'f', 0);
        painter.drawText(QRect(px - 30, content.bottom() + 5, 60, 15), Qt::AlignCenter, text);
    }

    // Y��
    for (float step = this->yminimum(); step <= this->ymaximum(); step += this->ystep())
    {
        float py = this->scaleY(step);

        // �̶���
        painter.drawLine(content.left() - 5, py, content.left(), py);

        // �̶�ֵ
        QString text = QString::number(step + this->yminimum(), 'f', 0);
        painter.drawText(QRect(0, py - 5, content.left(), 10), Qt::AlignCenter, text);
    }
}

// ����ͼ������
void PulseWidget::setDataF(const QList<float>& datas)
{
    // �������
    this->datas = datas;

    // ˢ�½���
    this->update();
}

// ���÷���������
void PulseWidget::setLineF(const QList<float>& lines)
{
    // �������
    this->lines = lines;

    // ˢ�½���
    this->update();
}