#include <QFont>
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

#include "tablewidget.h"


// 表头宽度
#define HEAD_WIDTH                   (120)      // 用于列模式
#define HEAD_HEIGHT                  (40)       // 用于行模式


class TableWidgetPrivate
{
public:
    TableWidgetPrivate();
    ~TableWidgetPrivate();

public:
    // 模式
    int mode;

    // 行列数
    int rows;
    int columns;

    // 当前列
    int current;

    // 选中状态
    QList<bool> selection;

    // 边框色
    QColor colorFrameIn;
    QColor colorFrameOut;

    // 背景色（标题）
    QColor backgroundHead;
    // 背景色（内容）
    QColor backgroundSelected;
    QColor backgroundUnselected;

    // 前景色（标题）
    QColor foregroundHead;
    // 前景色（内容）
    QColor foregroundContent;

    // 前景色（特定内容）
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
    // 模式
    d->mode = mode;

    // 默认行列数
    this->setRows(8);
    this->setColumns(10);
}

TableWidget::~TableWidget()
{
    delete d;
}

// 行列数
int TableWidget::rows() const
{
    return d->rows;
}

void TableWidget::setRows(int rows)
{
    // 行列数
    d->rows = rows;

    // 选中状态（默认未选中）
    this->clearSelect();
}

int TableWidget::columns() const
{
    return d->columns;
}

void TableWidget::setColumns(int columns)
{
    // 行列数
    d->columns = columns;

    // 选中状态（默认未选中）
    this->clearSelect();
}

// 模式
int TableWidget::mode() const
{
    return d->mode;
}

// 当前列
int TableWidget::current() const
{
    return d->current;
}

void TableWidget::setCurrent(int current)
{
    d->current = current;
}

// 选中状态
void TableWidget::clearSelect()
{
    d->selection.clear();

    // 默认都为选中
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

    // 刷新
    this->update();
}

// 设置颜色
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

// 选中模式（默认单选）
bool TableWidget::isSingleSelect() const
{
    return true;
}

// 获取表格内容
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

// 绘制事件
void TableWidget::paintEvent(QPaintEvent* event)
{
    if (TableWidget::ColumnMode == this->mode())
    {
        // 绘制内容
        this->drawContentColumnMode();

        // 绘制背景
        this->drawFrameColumnMode();
    }
    else
    {
        // 绘制内容
        this->drawContentRowMode();

        // 绘制背景
        this->drawFrameRowMode();
    }
}

// 鼠标事件
void TableWidget::mousePressEvent(QMouseEvent* event)
{
    // 默认处理
    QWidget::mousePressEvent(event);

    // 只响应鼠标左键
    if (Qt::LeftButton != event->button())
    {
        return;
    }

    // 位置检测，确定所选列
    if (TableWidget::ColumnMode == this->mode())
    {
        float columnWidth = 1.0 * (this->width() - HEAD_WIDTH) / this->columns();
        for (int column = 0; column < this->columns() && column < this->numOfItems(); column++)
        {
            // 垂直分隔线
            float x = (HEAD_WIDTH + column * columnWidth);
            QRect columnRect = QRect(x, 0, columnWidth, this->height());

            if (columnRect.contains(event->pos()))
            {
                // 当前列
                this->setCurrent(column);

                // 选中列
                if (this->isSingleSelect())
                {
                    this->clearSelect();
                }

                bool selected = !d->selection.at(column);
                this->setSelect(column, selected);

                // 上报信号
                emit columnClicked(column, selected);

                break;
            }
        }
    }
    else
    {
        QRect rect = this->rect();

        // 行高列宽
        float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
        // float columnWidth = 1.0 * rect.width() / this->columns();

        // 内边框
        for (int row = 0; row < this->rows() && row < this->numOfItems(); row++)
        {
            // 水平分隔线
            float y = rect.top() + HEAD_HEIGHT + row * rowHeight;
            QRect rowRect = QRect(rect.left(), y, rect.width(), rowHeight);

            if (rowRect.contains(event->pos()))
            {
                // 当前行
                this->setCurrent(row);

                // 选中列
                if (this->isSingleSelect())
                {
                    this->clearSelect();
                }

                bool selected = !d->selection.at(row);
                this->setSelect(row, selected);

                // 上报信号
                emit rowClicked(row, selected);

                break;
            }
        }
    }
}

// 绘制边框
void TableWidget::drawFrameRowMode()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // 行高列宽
    float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
    float columnWidth = 1.0 * rect.width() / this->columns();

    // 内边框
    painter.setPen(d->colorFrameIn);
    for (int row = 1; row < this->rows(); row++)
    {
        // 水平分隔线
        float y = rect.top() + HEAD_HEIGHT + row * rowHeight;
        painter.drawLine(rect.left(), y, rect.right(), y);

        // 垂直分隔线
        for (int column = 0; column < this->columns(); column++)
        {
            float x = (rect.left() + column * columnWidth);
            painter.drawLine(x, rect.top(), x, rect.bottom());
        }
    }

    // 外边框
    painter.setPen(d->colorFrameOut);
    painter.drawRect(rect.adjusted(0, 0, -1, -1));
}

void TableWidget::drawFrameColumnMode()
{
    QPainter painter(this);
    QRect rect = this->rect();

    // 行高列宽
    float rowHeight = 1.0 * rect.height() / this->rows();
    float columnWidth = 1.0 * (rect.width() - HEAD_WIDTH) / this->columns();

    // 内边框
    painter.setPen(d->colorFrameIn);
    for (int column = 0; column < this->columns(); column++)
    {
        // 垂直分隔线
        float x = (rect.left() + HEAD_WIDTH + column * columnWidth);
        painter.drawLine(x, rect.top(), x, rect.bottom());

        // 水平分隔线
        for (int row = 1; row < this->rows(); row++)
        {
            float y = rect.top() + row * rowHeight;
            painter.drawLine(rect.left(), y, rect.right(), y);
        }
    }

    // 外边框
    painter.setPen(d->colorFrameOut);
    painter.drawRect(rect.adjusted(0, 0, -1, -1));
}

// 绘制内容
void TableWidget::drawContentRowMode()
{
    QPainter painter(this);
    QRect rect = this->rect();
    QFont font = painter.font();

    // 行高列宽
    float rowHeight = 1.0 * (rect.height() - HEAD_HEIGHT) / this->rows();
    float columnWidth = 1.0 * rect.width() / this->columns();

    // 表头
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

    // 表格
    for (int row = 0; row < this->rows(); row++)
    {
        QStringList rowText = this->rowText(row);

        float x = rect.left();
        float y = rect.top() + HEAD_HEIGHT + row * rowHeight;

        if (rowText.isEmpty())
        {
            // 背景
            painter.fillRect(x, y, rect.width(), rowHeight, Qt::lightGray);
        }
        else
        {
            // 背景
            QColor backgroundContent = (d->selection.at(row) ? d->backgroundSelected : d->backgroundUnselected);
            painter.fillRect(x, y, rect.width(), rowHeight, backgroundContent);

            for (int column = 0; column < this->columns() && column < rowText.length(); column++)
            {
                // 前景
                int key = (row * 1000 + column);

                QColor foregroundContent = d->foregroundContents.value(key, d->foregroundContent);
                painter.setPen(foregroundContent);

                // 单元格内容（当前列，表头增加*）
                QString text = ((0 == column && d->current == row) ? "* " : "");
                text += rowText.at(column);

                // 字体
                font.setBold(0 == column);
                painter.setFont(font);

                // 绘制单元格内容
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
    
    // 行高列宽
    float rowHeight = 1.0 * rect.height() / this->rows();
    float columnWidth = 1.0 * (rect.width() - HEAD_WIDTH) / this->columns();

    // 表头
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

    // 表格
    for (int column = 0; column < this->columns(); column++)
    {
        float x = (rect.left() + HEAD_WIDTH + column * columnWidth);
        float y = rect.top();

        // 背景
        QColor backgroundContent = (d->selection.at(column) ? d->backgroundSelected : d->backgroundUnselected);
        painter.fillRect(x, rect.top(), columnWidth, rect.height(), backgroundContent);

        // 前景
        QStringList columnText = this->columnText(column);
        for (int row = 0; row < this->rows() && row < columnText.length(); row++)
        {
            // 前景
            int key = (row * 1000 + column);

            QColor foregroundContent = d->foregroundContents.value(key, d->foregroundContent);
            painter.setPen(foregroundContent);

            // 单元格内容（当前列，表头增加*）
            QString text = ((0 == row && d->current == column) ? "* " : "");
            text += columnText.at(row);

            // 字体
            font.setBold(0 == row);
            painter.setFont(font);

            // 绘制单元格内容
            painter.drawText(QRect(x, y + rowHeight * row, columnWidth, rowHeight), Qt::AlignCenter, text);
        }
    }
}