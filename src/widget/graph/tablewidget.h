#ifndef _TABLE_WIDGET_H_
#define _TABLE_WIDGET_H_


#include <QWidget>

#include "libwidget.h"

class TableWidgetPrivate;


// ���ؼ�
class WIDGET_EXPORT TableWidget : public QWidget
{
    Q_OBJECT

public:
    enum TableMode
    {
        RowMode = 0x01, // ��ģʽ��Ĭ�ϣ�
        ColumnMode = 0x02, // ��ģʽ
    };

public:
    TableWidget(int mode, QWidget* parent = 0);
    virtual ~TableWidget();

    // ������
    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    // ģʽ
    int mode() const;

    // ��ǰ����
    int current() const;
    void setCurrent(int current);

    // ѡ��״̬
    void clearSelect();
    void setSelect(int no, bool selected);

    // ������ɫ
    void clearColors();

    void setColor(int row, int column, const QColor& foregroundContent);

    void setColor(const QColor& colorFrameIn, const QColor& colorFrameOut, 
                  const QColor& backgroundHead, const QColor& backgroundSelected, const QColor& backgroundUnselected, 
                  const QColor& foregroundHead, const QColor& foregroundContent);

signals:
    // ��ѡ��
    void rowClicked(int row, bool selected);
    // ��ѡ��
    void columnClicked(int column, bool selected);

protected:
    // ѡ��ģʽ����ѡ��
    virtual bool isSingleSelect() const;

    // ��ȡ��ͷ����
    virtual QStringList headText() const = 0;

    // ��ȡ�������
    virtual int numOfItems() = 0;

    virtual QStringList rowText(int row);
    virtual QStringList columnText(int column);

protected:
    // �����¼�
    virtual void paintEvent(QPaintEvent* event);

    // ����¼�
    virtual void mousePressEvent(QMouseEvent* event);

private:
    // ���Ʊ߿�
    virtual void drawFrameRowMode();
    virtual void drawFrameColumnMode();

    // ��������
    virtual void drawContentRowMode();
    virtual void drawContentColumnMode();

private:
    TableWidgetPrivate* d;
};


#endif // _TABLE_WIDGET_H_