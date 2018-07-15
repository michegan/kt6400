#ifndef _GRAPH_WIDGET_H_
#define _GRAPH_WIDGET_H_


#include <QtGui/QWidget>

#include "libwidget.h"


class GraphWidgetPrivate;


// 图形控件
class WIDGET_EXPORT GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget* parent = 0);
    virtual ~GraphWidget();

    // 标题
    void setTitle(const QString& title);

    // 坐标轴名称
    QString xname() const;
    QString yname() const;

    void setName(const QString& xname, const QString& yname);

    // 坐标轴刻度
    float xstep() const;
    float xminimum() const;
    float xmaximum() const;
    
    void setXAxis(float minimum, float maximum, float step);

    float ystep() const;
    float yminimum() const;
    float ymaximum() const;
    
    void setYAxis(float minimum, float maximum, float step);

    // 边距
    void setMargin(float left, float right, float top, float bottom);

    // 设置颜色
    QColor colorAxis() const;
    QColor colorGraph() const;

    void setColor(const QColor& graph);
    void setColor(const QColor& background, const QColor& title, const QColor& graph, const QColor& axis);

protected:
    // 绘制事件
    virtual void paintEvent(QPaintEvent* event);

protected:
    // 内容矩形
    virtual QRect content();

    // 绘制图形
    virtual void drawGraph() = 0;

    // 刻度点
    virtual float scaleX(float x);
    virtual float scaleY(float y);

    // 图像点
    virtual float graphX(float x) = 0;
    virtual float graphY(float y) = 0;

private:
    // 绘制坐标轴
    void drawAxis();

    // 绘制标题
    void drawTitle();

    // 绘制背景
    void drawBackground();

private:
    GraphWidgetPrivate* d;
};


#endif // _GRAPH_WIDGET_H_