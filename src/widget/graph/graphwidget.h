#ifndef _GRAPH_WIDGET_H_
#define _GRAPH_WIDGET_H_


#include <QtGui/QWidget>

#include "libwidget.h"


class GraphWidgetPrivate;


// ͼ�οؼ�
class WIDGET_EXPORT GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget* parent = 0);
    virtual ~GraphWidget();

    // ����
    void setTitle(const QString& title);

    // ����������
    QString xname() const;
    QString yname() const;

    void setName(const QString& xname, const QString& yname);

    // ������̶�
    float xstep() const;
    float xminimum() const;
    float xmaximum() const;
    
    void setXAxis(float minimum, float maximum, float step);

    float ystep() const;
    float yminimum() const;
    float ymaximum() const;
    
    void setYAxis(float minimum, float maximum, float step);

    // �߾�
    void setMargin(float left, float right, float top, float bottom);

    // ������ɫ
    QColor colorAxis() const;
    QColor colorGraph() const;

    void setColor(const QColor& graph);
    void setColor(const QColor& background, const QColor& title, const QColor& graph, const QColor& axis);

protected:
    // �����¼�
    virtual void paintEvent(QPaintEvent* event);

protected:
    // ���ݾ���
    virtual QRect content();

    // ����ͼ��
    virtual void drawGraph() = 0;

    // �̶ȵ�
    virtual float scaleX(float x);
    virtual float scaleY(float y);

    // ͼ���
    virtual float graphX(float x) = 0;
    virtual float graphY(float y) = 0;

private:
    // ����������
    void drawAxis();

    // ���Ʊ���
    void drawTitle();

    // ���Ʊ���
    void drawBackground();

private:
    GraphWidgetPrivate* d;
};


#endif // _GRAPH_WIDGET_H_