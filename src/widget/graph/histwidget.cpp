#include <QFile>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainterPath>

#include "histinfo.h"
#include "histwidget.h"


class HistWidgetPrivate
{
public:
    HistWidgetPrivate();
    ~HistWidgetPrivate();

public:
    // �Ƿ�ɱ༭
    bool editable;

    // �Ƿ����
    bool fillHist;

    // ��ǰ������
    int currentLine;

    // ͼ������
    QList<float> datas;
    QList<float> lines;
};

HistWidgetPrivate::HistWidgetPrivate()
    : editable(false), fillHist(false), currentLine(-1)
{

}

HistWidgetPrivate::~HistWidgetPrivate()
{

}


HistWidget::HistWidget(QWidget* parent)
    : GraphWidget(parent), d(new HistWidgetPrivate())
{
    // ����
    this->setTitle("Hist");
}

HistWidget::~HistWidget()
{
    delete d;
}

// ���ֱ��ͼ
void HistWidget::clear()
{
    // �������
    d->datas.clear();
    d->lines.clear();

    // ˢ�½���
    this->update();
}

// �Ƿ�ɱ༭
void HistWidget::setEditable(bool editable)
{
    d->editable = editable;

    // ˢ��
    this->update();
}

// �������
void HistWidget::setFillHist(bool fillHist)
{
    d->fillHist = fillHist;
}

// ����ֱ��ͼ��Ϣ
void HistWidget::setHistInfo(const HistInfo& histInfo)
{
    // ֱ��ͼ����
    this->setData<int>(histInfo.datas, histInfo.dataLen);

    // ����������
    this->setLine<int>(histInfo.lines, histInfo.lineLen);
}


// �����¼�
void HistWidget::keyPressEvent(QKeyEvent* event)
{
    GraphWidget::keyPressEvent(event);

    // �Ǳ༭״̬
    if (d->editable)
    {
        int key = event->key();
        if (Qt::Key_Left == key)
        {
            if (0 <= d->currentLine)
            {
                int x = d->lines.at(d->currentLine);
                if (this->xminimum() < x)
                {
                    d->lines[d->currentLine] = x - 1;

                    // ˢ��
                    this->update();
                }
            }
        }
        else if (Qt::Key_Right == key)
        {
            if (0 <= d->currentLine)
            {
                int x = d->lines.at(d->currentLine);
                if (x < this->xmaximum())
                {
                    d->lines[d->currentLine] = x + 1;

                    // ˢ��
                    this->update();
                }
            }
        }
        else if (Qt::Key_1 <= key && key <= Qt::Key_9)
        {
            int line = key - Qt::Key_1;
            if (0 <= line && line < d->lines.length())
            {
                d->currentLine = line;
            }
        }
    }
}

// ����¼�
void HistWidget::mousePressEvent(QMouseEvent* event)
{
    GraphWidget::mousePressEvent(event);

    do 
    {
        // �Ǳ༭״̬
        if (!d->editable)
        {
            break;
        }

        // �����
        if (Qt::LeftButton != event->button())
        {
            break;
        }

        // ���ݾ���
        QRect rect = this->content();
        if (!rect.contains(event->pos()))
        {
            break;
        }

        // ��ý��㣬���ϱ�����¼�
        this->setFocus();

        emit clicked();
    } while (0);
}

// ����ͼ��
void HistWidget::drawGraph()
{
    // ����ֱ��ͼ
    if (!d->datas.isEmpty())
    {
        this->drawHist();
    }

    // ���Ʒ�����
    if (!d->lines.isEmpty())
    {
        this->drawLine();
    }

    // ���ƿ̶�ֵ
    this->drawScale();
}

// �̶ȵ�
float HistWidget::scaleX(float x)
{
    QRect content = this->content();
    float scale = 1.0 * content.width() / (this->xmaximum() - this->xminimum());

    return (content.left() + x * scale);
}

// ͼ���
float HistWidget::graphX(float x)
{
    QRect content = this->content();
    float scale = 1.0 * content.width() / d->datas.length();

    return (content.left() + x * scale);
}

float HistWidget::graphY(float y)
{
    QRect content = this->content();
    float scale = 1.0 * content.height() / (this->ymaximum() - this->yminimum());

    return (content.bottom() - (y - this->yminimum()) * scale);
}

// ����ֱ��ͼ
void HistWidget::drawHist()
{
    QPainterPath path;
    QPainter painter(this);
    QRect content = this->content();

    // ����ԭ��
    path.moveTo(content.left(), content.bottom());

    // ֱ��ͼ
    for (int i = 0; i < d->datas.length(); i++)
    {
        float data = d->datas.at(i);

        float px = this->graphX(i);
        float py = qMax<float>(content.top(), this->graphY(data));

        path.lineTo(px, py);
    }

    // ȷ���ص�X����
    if (d->fillHist)
    {
        path.lineTo(content.right(), content.bottom());
    }

    // ����ֱ��ͼ
    if (d->fillHist)
    {
        // ʵ��
        QBrush brush(this->colorGraph());
        painter.fillPath(path, brush);
    }
    else
    {
        // ����
        painter.setPen(this->colorGraph());
        painter.drawPath(path);
    }
}

// ���Ʒ�����
void HistWidget::drawLine()
{
    QPainter painter(this);
    QRect content = this->content();

    // ����
    painter.setPen(this->colorAxis());

    // ������
    for (int i = 0; i < d->lines.length(); i++)
    {
        int px = this->scaleX(d->lines.at(i));

        painter.drawLine(px, content.bottom(), px, content.top());
    }
}

// ���ƿ̶�ֵ
void HistWidget::drawScale()
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
}

// ����ͼ������
void HistWidget::setDataF(const QList<float>& datas)
{
    // �������
    d->datas = datas;

    // ˢ�½���
    this->update();
}

// ���÷���������
void HistWidget::setLineF(const QList<float>& lines)
{
    // �������
    d->lines = lines;

    // ˢ�½���
    this->update();
}


// WBCֱ��ͼ
WbcHistWidget::WbcHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // ����
    this->setTitle("WBC");

    // �������
    this->setFillHist(true);

    // ����������
    this->setName("fL", "");

    // ������̶�
    this->setXAxis(0, 360, 100);
    this->setYAxis(0, 88, 88);

    // ������ɫ
    this->setColor(Qt::white);

    // ��������
    this->setHistInfo(WbcHistInfo());
}

WbcHistWidget::~WbcHistWidget()
{

}


// RBCֱ��ͼ
RbcHistWidget::RbcHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // ����
    this->setTitle("RBC");

    // �������
    this->setFillHist(true);

    // ����������
    this->setName("fL", "");

    // ������̶�
    this->setXAxis(0, 320, 100);
    this->setYAxis(0, 88, 88);

    // ������ɫ
    this->setColor(Qt::red);

    // ��������
    this->setHistInfo(RbcHistInfo());
}

RbcHistWidget::~RbcHistWidget()
{

}


// PLTֱ��ͼ
PltHistWidget::PltHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // ����
    this->setTitle("PLT");

    // �������
    this->setFillHist(true);

    // ����������
    this->setName("fL", "");

    // ������̶�
    this->setXAxis(0, 40, 10);
    this->setYAxis(0, 88, 88);

    // ������ɫ
    this->setColor(Qt::green);

    // ��������
    this->setHistInfo(PltHistInfo());
}

PltHistWidget::~PltHistWidget()
{

}