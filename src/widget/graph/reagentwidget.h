#ifndef _REAGENT_WIDGET_H_
#define _REAGENT_WIDGET_H_


#include <QMap>
#include <QtGui/QWidget>

#include "libwidget.h"


// 试剂控件
class WIDGET_EXPORT ReagentWidget : public QWidget
{
    Q_OBJECT

public:
    ReagentWidget(QWidget* parent = 0);
    virtual ~ReagentWidget();

    // 试剂颜色（正常态颜色，异常态统一红色）
    void setColor(int reagent, const QColor& color);

signals:
    // 鼠标点击
    void clicked();

protected:
    // 绘制事件
    virtual void paintEvent(QPaintEvent* event);

    // 鼠标事件
    virtual void mousePressEvent(QMouseEvent* event);

private:
    // 内容矩形
    QRect content();

private:
    // 试剂颜色（正常态颜色，异常态统一红色）
    QMap<int, QColor> colors;
};


#endif // _REAGENT_WIDGET_H_