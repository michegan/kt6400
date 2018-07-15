#include <QFont>
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

#include "tablewidget.h"


// ��ͷ���
#define HEAD_WIDTH                   (120)      // ������ģʽ
#define HEAD_HEIGHT                  (40)       // ������ģʽ


class TableWidgetPrivate
{
public:
    TableWidgetPrivate();
    ~TableWidgetPrivate();

public:
    // ģʽ
    int mode;

    // ������
    int rows;
    int columns;

    // ��ǰ��
    int current;

    // ѡ��״̬
    QList<bool> selection;

    // �߿�ɫ
    QColor colorFrameIn;
    QColor colorFrameOut;

    // ����ɫ�����⣩
    QColor backgroundHead;
    // ����ɫ�����ݣ�
    QColor backgroundSelected;
    QColor backgroundUnselected;

    // ǰ��ɫ�����⣩
    QColor foregroundHead;
    // ǰ��ɫ�����ݣ�
    QColor foregroundContent;

    // ǰ��ɫ���ض����ݣ�
    QMap<int, QColor> foregroundContents;
};

TableWidgetPrivate::TableWidgetPrivate()
    : mode(TableWidget::RowMode), rows(0), columns(0), current(-1), colorFrameIn(Qt::lightGray), colorFrameOut(Qt::darkGray),
      backgroundHead(QColor(68, 112, 149)), backgroundSelected(QColor(220, 220, 220)), backgroundUnselected(QColor(255, 255, 255)), 
      foregroundHead(QColor(255, 255, 255)), foregroundContent(Qt::black)
{

}

TableWidgetPrivate::~TableWidgetPrivate()
{

}


TableWidget::TableWidget(int mode, QWidget* parent)
    : QWidget(parent), d(new TableWidgetPrivate())
{
    // ģʽ
    d->mode = mode;

    // Ĭ��������
    this->setRows(8);
    this->setColumns(10);
}

TableWidget::~TableWidget()
{
    delete d;
}

// ������
int TableWidget::rows() const
{
    return d->rows;
}

void TableWidget::setRows(int rows)
{
    // ������
    d->rows = rows;

    // ѡ��״̬��Ĭ��δѡ�У�
    this->clearSelect();
}

int TableWidget::columns() const
{
    return d->columns;
}

void TableWidget::setColumns(int columns)
{
    // ������
    d->columns = columns;

    // ѡ��״̬��Ĭ��δѡ�У�
    this->clearSelect();
}

// ģʽ
int TableWidget::mode() const
{
    return d->mode;
}

// ��ǰ��
int TableWidget::current() const
{
    return d->current;
}

void TableWidget::setCurrent(int current)
{
    d->current = current;
}

// ѡ��״̬
void TableWidget::clearSelect()
{
    d->selection.clear();

    // Ĭ�϶�Ϊѡ��
    int items = (TableWidget::RowMode == this->mode() ? this->rows() : this->columns());
    for (int i = 0; i < items; i++)
    {
        d->selection.append(false);
    }
}

void TableWidget::setSelect(int no, bool selected)
{
    if (TableWidget::ColumnMode == this->mode())
    {
        if (0 <= no && no < this->columns())
        {
            d->selection[no] = selected;
        }
        else
        {
            qWarning() << "TableWidget setSelect invalid column" << no;
        }
    }
    else
    {
        if (0 <= no && no < this->rows())
        {
            d->selection[no] = selected;
        }
        else
        {
            qWarning() << "TableWidget setSelect invalid row" << no;
        }
    }

    // ˢ��
    this->update();
}

// ������ɫ
void TableWidget::clearColors()
{
    d->foregroundContents.clear();
}

void TableWidget::setColor(int row, int column, const QColor& foregroundContent)
{
    int key = row * 1000 + column;
    if (d->foregroundContents.contains(key))
    {
        d->foregroundContents[key] = foregroundContent;
    }
    else
    {
        d->foregroundContents.insert(key, foregroundContent);
    }
}

void TableWidget::setColor(const QColor& colorFrameIn, const QColor& colorFrameOut, 
                           const QColor& backgroundHead, const QColor& backgroundSelected, const QColor& backgroundUnselected, 
                           const QColor& foregroundHead, const QColor& foregroundContent)
{
    d->colorFrameIn = colorFrameIn;
    d->colorFrameOut = colorFrameOut;
    d->backgroundHead = backgroundHead;
    d->backgroundSelected = backgroundSelected;
    d->backgroundUnselected = backgroundUnselected;
    d->foregroundHead = foregroundHead;
    d->foregroundContent = foregroundContent;
}

// ѡ��ģʽ��Ĭ�ϵ�ѡ��
bool TableWidget::isSingleSelect() const
{
    return true;
}

// ��ȡ�������
QStringList TableWidget::rowText(int row)
{
    QStringList text;
    for (int column = 0; column < this->columns(); column++)
    {
        text.append(QString("%1-%2").arg(row).arg(column));
    }
    return text;
}

QStringList TableWidget::columnText(int column)
{
    QStringList text;
    for (int row = 0; row < this->rows(); row++)
    {
        text.append(QString("%1-%2").arg(row).arg(column));
    }
    return text;
}

// �����¼�
void TableWidget::paintEvent(QPaintEvent* event)
{
    if (TableWidget::ColumnMode == this->mode())
    {
        // ��������
        this->drawContentColumnMode();

        // ���Ʊ���
        this->drawFrameColumnMode();
    }
    else
    {
        // ��������
        this->drawContentRowMode();

        // ���Ʊ���
        this->drawFrameRowMode();
    }
}

// ����¼�
void TableWidget::mousePressEvent(QMouseEvent* event)
{
    // Ĭ�ϴ���
    QWidget::mousePressEvent(event);

    // ֻ��Ӧ������
    if (Qt::LeftButton != event->button())
    {
        return;
    }

    // λ�ü�⣬ȷ����ѡ��
    if (TableWidget::ColumnMode == this->mode())
    {
        float columnWidth = 1.0 * (this->width() - HEAD_WIDTH) / this->columns();
        for (int column = 0; column < this->columns() && column < this->numOfItems(); column++)
        {
            // ��ֱ�ָ���
            float x = (HEAD_WIDTH + column * columnWidth);
            QRect columnRect = QRect(x, 0, columnWidth, this->height());

            if (columnRect.contains(event->pos()))
            {
                // ��ǰ��
                this->setCurrent(column);

                // ѡ����
                if (this->isSingleSelect())
                {
                    this->clearSelect();
                }

                bool selected = !d->selection.at(column);
                this->setSelect(column, selected);

                // �ϱ��ź�
                emit columnClicked(column, selected);

                break;
            }
        }
    }
    else
    {
        QRect rect = this->rect();

        // �и��п�
        float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
        // float columnWidth = 1.0 * rect.width() / this->columns();

        // �ڱ߿�
        for (int row = 0; row < this->rows() && row < this->numOfItems(); row++)
        {
            // ˮƽ�ָ���
            float y = rect.top() + HEAD_HEIGHT + row * rowHeight;
            QRect rowRect = QRect(rect.left(), y, rect.width(), rowHeight);

            if (rowRect.contains(event->pos()))
            {
                // ��ǰ��
                this->setCurrent(row);

                // ѡ����
                if (this->isSingleSelect())
                {
                    this->clearSelect();
                }

                bool selected = !d->selection.at(row);
                this->setSelect(row, selected);

                // �ϱ��ź�
                emit rowClicked(row, selected);

                break;
            }
        }
    }
}

// ���Ʊ߿�
void TableWidget::drawFrameRowMode()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // �и��п�
    float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
    float columnWidth = 1.0 * rect.width() / this->columns();

    // �ڱ߿�
    painter.setPen(d->colorFrameIn);
    for (int row = 1; row < this->rows(); row++)
    {
        // ˮƽ�ָ���
        float y = rect.top() + HEAD_HEIGHT + row * rowHeight;
        painter.drawLine(rect.left(), y, rect.right(), y);

        // ��ֱ�ָ���
        for (int column = 0; column < this->columns(); column++)
        {
            float x = (rect.left() + column * columnWidth);
            painter.drawLine(x, rect.top(), x, rect.bottom());
        }
    }

    // ��߿�
    painter.setPen(d->colorFrameOut);
    painter.drawRect(rect.adjusted(0, 0, -1, -1));
}

void TableWidget::drawFrameColumnMode()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // �и��п�
    float rowHeight = 1.0 * rect.height() / this->rows();
    float columnWidth = 1.0 * (rect.width() - HEAD_WIDTH) / this->columns();

    // �ڱ߿�
    painter.setPen(d->colorFrameIn);
    for (int column = 0; column < this->columns(); column++)
    {
        // ��ֱ�ָ���
        float x = (rect.left() + HEAD_WIDTH + column * columnWidth);
        painter.drawLine(x, rect.top(), x, rect.bottom());

        // ˮƽ�ָ���
        for (int row = 1; row < this->rows(); row++)
        {
            float y = rect.top() + row * rowHeight;
            painter.drawLine(rect.left(), y, rect.right(), y);
        }
    }

    // ��߿�
    painter.setPen(d->colorFrameOut);
    painter.drawRect(rect.adjusted(0, 0, -1, -1));
}

// ��������
void TableWidget::drawContentRowMode()
{
    QPainter painter(this);
    QRect rect = this->rect();
    QFont font = painter.font();

    // �и��п�
    float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
    float columnWidth = 1.0 * rect.width() / this->columns();

    // ��ͷ
    painter.fillRect(rect.left(), rect.top(), rect.width(), HEAD_HEIGHT, d->backgroundHead);

    float x = rect.left();
    painter.setPen(d->foregroundHead);

    QStringList headText = this->headText();
    for (int column = 0; column < this->columns() && column < headText.length(); column++)
    {
        font.setBold(true);
        painter.setFont(font);

        QString text = headText.at(column);
        painter.drawText(QRect(x + columnWidth * column, rect.top(), columnWidth, HEAD_HEIGHT), Qt::AlignCenter, text);
    }

    // ���
    for (int row = 0; row < this->rows(); row++)
    {
        QStringList rowText = this->rowText(row);

        float x = rect.left();
        float y = rect.top() + HEAD_HEIGHT + row * rowHeight;

        if (rowText.isEmpty())
        {
            // ����
            painter.fillRect(x, y, rect.width(), rowHeight, Qt::lightGray);
        }
        else
        {
            // ����
            QColor backgroundContent = (d->selection.at(row) ? d->backgroundSelected : d->backgroundUnselected);
            painter.fillRect(x, y, rect.width(), rowHeight, backgroundContent);

            for (int column = 0; column < this->columns() && column < rowText.length(); column++)
            {
                // ǰ��
                int key = (row * 1000 + column);

                QColor foregroundContent = d->foregroundContents.value(key, d->foregroundContent);
                painter.setPen(foregroundContent);

                // ��Ԫ�����ݣ���ǰ�У���ͷ����*��
                QString text = ((0 == column && d->current == row) ? "* " : "");
                text += rowText.at(column);

                // ����
                font.setBold(0 == column);
                painter.setFont(font);

                // ���Ƶ�Ԫ������
                painter.drawText(QRect(x + columnWidth * column, y, columnWidth, rowHeight), Qt::AlignCenter, text);
            }
        }
    }
}

void TableWidget::drawContentColumnMode()
{
    QPainter painter(this);
    QRect rect = this->rect();
    QFont font = painter.font();
    
    // �и��п�
    float rowHeight = 1.0 * rect.height() / this->rows();
    float columnWidth = 1.0 * (rect.width() - HEAD_WIDTH) / this->columns();

    // ��ͷ
    painter.fillRect(rect.left(), rect.top(), HEAD_WIDTH, rect.height(), d->backgroundHead);

    float y = rect.top();
    painter.setPen(d->foregroundHead);

    QStringList headText = this->headText();
    for (int row = 0; row < this->rows() && row < headText.length(); row++)
    {
        font.setBold(true);
        painter.setFont(font);

        QString text = headText.at(row);
        painter.drawText(QRect(rect.left(), y + rowHeight * row, HEAD_WIDTH, rowHeight), Qt::AlignCenter, text);
    }

    // ���
    for (int column = 0; column < this->columns(); column++)
    {
        float x = (rect.left() + HEAD_WIDTH + column * columnWidth);
        float y = rect.top();

        // ����
        QColor backgroundContent = (d->selection.at(column) ? d->backgroundSelected : d->backgroundUnselected);
        painter.fillRect(x, rect.top(), columnWidth, rect.height(), backgroundContent);

        // ǰ��
        QStringList columnText = this->columnText(column);
        for (int row = 0; row < this->rows() && row < columnText.length(); row++)
        {
            // ǰ��
            int key = (row * 1000 + column);

            QColor foregroundContent = d->foregroundContents.value(key, d->foregroundContent);
            painter.setPen(foregroundContent);

            // ��Ԫ�����ݣ���ǰ�У���ͷ����*��
            QString text = ((0 == row && d->current == column) ? "* " : "");
            text += columnText.at(row);

            // ����
            font.setBold(0 == row);
            painter.setFont(font);

            // ���Ƶ�Ԫ������
            painter.drawText(QRect(x, y + rowHeight * row, columnWidth, rowHeight), Qt::AlignCenter, text);
        }
    }
}