#include <QFont>
#include <QPainter>
#include <QMouseEvent>

#include "reagent.h"
#include "reagentwidget.h"


// �߾�
#define MARGIN              (3)


ReagentWidget::ReagentWidget(QWidget* parent)
    : QWidget(parent)
{

}

ReagentWidget::~ReagentWidget()
{

}

// �Լ���ɫ������̬��ɫ���쳣̬ͳһ��ɫ��
void ReagentWidget::setColor(int reagent, const QColor& color)
{
    // ������ɫ
    if (this->colors.contains(reagent))
    {
        this->colors[reagent] = color;
    }
    else
    {
        this->colors.insert(reagent, color);
    }

    // ˢ��
    this->update();
}

// �����¼�
void ReagentWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect content = this->content();

    // �Լ��б�
    QList<int> reagents = Reagent::reagents();
    int rows = reagents.length();

    // �и��п�
    float rowHeight = (content.height() - (rows - 1) * MARGIN) / rows;

    // ����ÿ���Լ�
    float x = content.left();
    float y = content.top();

    for (int i = 0; i < reagents.length(); i++)
    {
        // �Լ�״̬������ɫ
        int reagent = reagents.at(i);

        Reagent::setRemain(reagent, 50);
        Reagent::setVolume(reagent, 130);

        QColor color = Qt::green;
        if (Reagent::isEmpty(reagent))
        {
            // ��
            color = QColor(243, 115, 112);
        }
        else if (Reagent::isEnough(reagent))
        {
            // �㹻
            color = QColor(248, 225, 61);
        }
        else
        {
            // ����
            color = QColor(170, 218, 20);
        }

        // ��߿�
        painter.setPen(color);

        QRect rect = QRect(x, y, content.width(), rowHeight);
        painter.drawRoundedRect(rect, MARGIN, MARGIN);

        // �б߿�
        // painter.setPen(QColor(8, 8, 6));

        // rect.adjust(1, 1, -1, -1);
        // painter.drawRoundedRect(rect, MARGIN, MARGIN);

        // �ڱ߿�
        rect.adjust(3, 3, -2, -2);

        if (Reagent::isEmpty(reagent))
        {
            painter.fillRect(rect, color);
        }
        else
        {
            float remain = Reagent::remain(reagent);
            float volume = Reagent::volume(reagent);

            rect.setWidth(rect.width() * remain / volume);

            painter.fillRect(rect, color);
        }

        y += (rowHeight + MARGIN);
    }
}

// ����¼�
void ReagentWidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    // ���
    if (Qt::LeftButton == event->button())
    {
        // ���ݾ���
        QRect rect = this->content();
        if (rect.contains(event->pos()))
        {
            // ��ý��㣬���ϱ�����¼�
            this->setFocus();

            emit clicked();
        }
    }
}

// ���ݾ���
QRect ReagentWidget::content()
{
    int width = (this->width() - 2 * MARGIN);
    int height = (this->height() - 2 * MARGIN);

    return QRect(MARGIN, MARGIN, qMax<int>(width, 0), qMax<int>(height, 0));
}