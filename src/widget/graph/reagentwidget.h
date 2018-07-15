#ifndef _REAGENT_WIDGET_H_
#define _REAGENT_WIDGET_H_


#include <QMap>
#include <QtGui/QWidget>

#include "libwidget.h"


// �Լ��ؼ�
class WIDGET_EXPORT ReagentWidget : public QWidget
{
    Q_OBJECT

public:
    ReagentWidget(QWidget* parent = 0);
    virtual ~ReagentWidget();

    // �Լ���ɫ������̬��ɫ���쳣̬ͳһ��ɫ��
    void setColor(int reagent, const QColor& color);

signals:
    // �����
    void clicked();

protected:
    // �����¼�
    virtual void paintEvent(QPaintEvent* event);

    // ����¼�
    virtual void mousePressEvent(QMouseEvent* event);

private:
    // ���ݾ���
    QRect content();

private:
    // �Լ���ɫ������̬��ɫ���쳣̬ͳһ��ɫ��
    QMap<int, QColor> colors;
};


#endif // _REAGENT_WIDGET_H_