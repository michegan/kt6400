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
    // 是否可编辑
    bool editable;

    // 是否填充
    bool fillHist;

    // 当前分类线
    int currentLine;

    // 图形数据
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
    // 标题
    this->setTitle("Hist");
}

HistWidget::~HistWidget()
{
    delete d;
}

// 清空直方图
void HistWidget::clear()
{
    // 清空数据
    d->datas.clear();
    d->lines.clear();

    // 刷新界面
    this->update();
}

// 是否可编辑
void HistWidget::setEditable(bool editable)
{
    d->editable = editable;

    // 刷新
    this->update();
}

// 设置填充
void HistWidget::setFillHist(bool fillHist)
{
    d->fillHist = fillHist;
}

// 设置直方图信息
void HistWidget::setHistInfo(const HistInfo& histInfo)
{
    // 直方图数据
    this->setData<int>(histInfo.datas, histInfo.dataLen);

    // 分类线数据
    this->setLine<int>(histInfo.lines, histInfo.lineLen);
}


// 键盘事件
void HistWidget::keyPressEvent(QKeyEvent* event)
{
    GraphWidget::keyPressEvent(event);

    // 非编辑状态
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

                    // 刷新
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

                    // 刷新
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

// 鼠标事件
void HistWidget::mousePressEvent(QMouseEvent* event)
{
    GraphWidget::mousePressEvent(event);

    do 
    {
        // 非编辑状态
        if (!d->editable)
        {
            break;
        }

        // 非左键
        if (Qt::LeftButton != event->button())
        {
            break;
        }

        // 内容矩形
        QRect rect = this->content();
        if (!rect.contains(event->pos()))
        {
            break;
        }

        // 获得焦点，并上报鼠标事件
        this->setFocus();

        emit clicked();
    } while (0);
}

// 绘制图形
void HistWidget::drawGraph()
{
    // 绘制直方图
    if (!d->datas.isEmpty())
    {
        this->drawHist();
    }

    // 绘制分类线
    if (!d->lines.isEmpty())
    {
        this->drawLine();
    }

    // 绘制刻度值
    this->drawScale();
}

// 刻度点
float HistWidget::scaleX(float x)
{
    QRect content = this->content();
    float scale = 1.0 * content.width() / (this->xmaximum() - this->xminimum());

    return (content.left() + x * scale);
}

// 图像点
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

// 绘制直方图
void HistWidget::drawHist()
{
    QPainterPath path;
    QPainter painter(this);
    QRect content = this->content();

    // 坐标原点
    path.moveTo(content.left(), content.bottom());

    // 直方图
    for (int i = 0; i < d->datas.length(); i++)
    {
        float data = d->datas.at(i);

        float px = this->graphX(i);
        float py = qMax<float>(content.top(), this->graphY(data));

        path.lineTo(px, py);
    }

    // 确保回到X轴上
    if (d->fillHist)
    {
        path.lineTo(content.right(), content.bottom());
    }

    // 绘制直方图
    if (d->fillHist)
    {
        // 实心
        QBrush brush(this->colorGraph());
        painter.fillPath(path, brush);
    }
    else
    {
        // 空心
        painter.setPen(this->colorGraph());
        painter.drawPath(path);
    }
}

// 绘制分类线
void HistWidget::drawLine()
{
    QPainter painter(this);
    QRect content = this->content();

    // 画笔
    painter.setPen(this->colorAxis());

    // 分类线
    for (int i = 0; i < d->lines.length(); i++)
    {
        int px = this->scaleX(d->lines.at(i));

        painter.drawLine(px, content.bottom(), px, content.top());
    }
}

// 绘制刻度值
void HistWidget::drawScale()
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
}

// 设置图形数据
void HistWidget::setDataF(const QList<float>& datas)
{
    // 填充数据
    d->datas = datas;

    // 刷新界面
    this->update();
}

// 设置分类线数据
void HistWidget::setLineF(const QList<float>& lines)
{
    // 填充数据
    d->lines = lines;

    // 刷新界面
    this->update();
}


// WBC直方图
WbcHistWidget::WbcHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // 标题
    this->setTitle("WBC");

    // 设置填充
    this->setFillHist(true);

    // 坐标轴名称
    this->setName("fL", "");

    // 坐标轴刻度
    this->setXAxis(0, 360, 100);
    this->setYAxis(0, 88, 88);

    // 设置颜色
    this->setColor(Qt::white);

    // 关联数据
    this->setHistInfo(WbcHistInfo());
}

WbcHistWidget::~WbcHistWidget()
{

}


// RBC直方图
RbcHistWidget::RbcHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // 标题
    this->setTitle("RBC");

    // 设置填充
    this->setFillHist(true);

    // 坐标轴名称
    this->setName("fL", "");

    // 坐标轴刻度
    this->setXAxis(0, 320, 100);
    this->setYAxis(0, 88, 88);

    // 设置颜色
    this->setColor(Qt::red);

    // 关联数据
    this->setHistInfo(RbcHistInfo());
}

RbcHistWidget::~RbcHistWidget()
{

}


// PLT直方图
PltHistWidget::PltHistWidget(QWidget* parent)
    : HistWidget(parent)
{
    // 标题
    this->setTitle("PLT");

    // 设置填充
    this->setFillHist(true);

    // 坐标轴名称
    this->setName("fL", "");

    // 坐标轴刻度
    this->setXAxis(0, 40, 10);
    this->setYAxis(0, 88, 88);

    // 设置颜色
    this->setColor(Qt::green);

    // 关联数据
    this->setHistInfo(PltHistInfo());
}

PltHistWidget::~PltHistWidget()
{

}