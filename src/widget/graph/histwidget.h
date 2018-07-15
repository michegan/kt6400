#ifndef _HIST_WIDGET_H_
#define _HIST_WIDGET_H_


#include "graphwidget.h"


class HistInfo;
class HistWidgetPrivate;


// 直方图
class WIDGET_EXPORT HistWidget : public GraphWidget
{
    Q_OBJECT

public:
    HistWidget(QWidget* parent = 0);
    virtual ~HistWidget();

    // 清空直方图
    virtual void clear();

    // 是否可编辑
    void setEditable(bool editable);

    // 设置填充
    void setFillHist(bool fillHist);

    // 设置直方图信息
    void setHistInfo(const HistInfo& histInfo);

public:
    // 设置图形数据
    template<typename T>
    void setData(const QList<T>& datas)
    {
        // 转换为float类型
        QList<float> fdatas;
        foreach (T data, datas)
        {
            fdatas.append(data);
        }

        // 设置图形数据
        this->setDataF(fdatas);
    }

    template<typename T>
    void setData(const T* datas, int dataLen)
    {
        // 转换为float类型
        QList<float> fdatas;
        for (int i = 0; i < dataLen; i++)
        {
            fdatas.append(*(datas + i));
        }

        // 设置图形数据
        this->setDataF(fdatas);
    }

    // 设置分类线数据
    template<typename T>
    void setLine(const QList<T>& lines)
    {
        {
            // 转换为float类型
            QList<float> flines;
            foreach (T line, lines)
            {
                flines.append(line);
            }

            // 设置图形数据
            this->setLineF(flines);
        }
    }

    template<typename T>
    void setLine(const T* lines, int lineLen)
    {
        {
            // 转换为float类型
            QList<float> flines;
            for (int i = 0; i < lineLen; i++)
            {
                flines.append(*(lines + i));
            }

            // 设置图形数据
            this->setLineF(flines);
        }
    }

signals:
    // 鼠标点击
    void clicked();

protected:
    // 键盘事件
    virtual void keyPressEvent(QKeyEvent* event);

    // 鼠标事件
    virtual void mousePressEvent(QMouseEvent* event);

protected:
    // 绘制图形
    virtual void drawGraph();

    // 刻度点
    virtual float scaleX(float x);

    // 图像点
    virtual float graphX(float x);
    virtual float graphY(float y);

private:
    // 绘制直方图
    virtual void drawHist();

    // 绘制分类线
    virtual void drawLine();

    // 绘制刻度值
    virtual void drawScale();

    // 设置图形数据
    void setDataF(const QList<float>& datas);

    // 设置分类线数据
    void setLineF(const QList<float>& lines);

private:
    HistWidgetPrivate* d;
};


// WBC直方图:
class WIDGET_EXPORT WbcHistWidget : public HistWidget
{
    Q_OBJECT

public:
    WbcHistWidget(QWidget* parent = 0);
    virtual ~WbcHistWidget();
};


// RBC直方图
class WIDGET_EXPORT RbcHistWidget : public HistWidget
{
    Q_OBJECT

public:
    RbcHistWidget(QWidget* parent = 0);
    virtual ~RbcHistWidget();
};


// PLT直方图
class WIDGET_EXPORT PltHistWidget : public HistWidget
{
    Q_OBJECT

public:
    PltHistWidget(QWidget* parent = 0);
    virtual ~PltHistWidget();
};


#endif // _HIST_WIDGET_H_