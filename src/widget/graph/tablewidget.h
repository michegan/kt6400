#ifndef _TABLE_WIDGET_H_
#define _TABLE_WIDGET_H_


#include <QWidget>

#include "libwidget.h"

class TableWidgetPrivate;


// 表格控件
class WIDGET_EXPORT TableWidget : public QWidget
{
    Q_OBJECT

public:
    enum TableMode
    {
        RowMode = 0x01, // 行模式（默认）
        ColumnMode = 0x02, // 列模式
    };

public:
    TableWidget(int mode, QWidget* parent = 0);
    virtual ~TableWidget();

    // 行列数
    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    // 模式
    int mode() const;

    // 当前行列
    int current() const;
    void setCurrent(int current);

    // 选中状态
    void clearSelect();
    void setSelect(int no, bool selected);

    // 设置颜色
    void clearColors();

    void setColor(int row, int column, const QColor& foregroundContent);

    void setColor(const QColor& colorFrameIn, const QColor& colorFrameOut, 
                  const QColor& backgroundHead, const QColor& backgroundSelected, const QColor& backgroundUnselected, 
                  const QColor& foregroundHead, const QColor& foregroundContent);

signals:
    // 行选中
    void rowClicked(int row, bool selected);
    // 列选中
    void columnClicked(int column, bool selected);

protected:
    // 选中模式（单选）
    virtual bool isSingleSelect() const;

    // 获取表头内容
    virtual QStringList headText() const = 0;

    // 获取表格内容
    virtual int numOfItems() = 0;

    virtual QStringList rowText(int row);
    virtual QStringList columnText(int column);

protected:
    // 绘制事件
    virtual void paintEvent(QPaintEvent* event);

    // 鼠标事件
    virtual void mousePressEvent(QMouseEvent* event);

private:
    // 绘制边框
    virtual void drawFrameRowMode();
    virtual void drawFrameColumnMode();

    // 绘制内容
    virtual void drawContentRowMode();
    virtual void drawContentColumnMode();

private:
    TableWidgetPrivate* d;
};


#endif // _TABLE_WIDGET_H_