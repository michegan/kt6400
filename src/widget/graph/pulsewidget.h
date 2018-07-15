#ifndef _PULSE_WIDGET_H_
#define _PULSE_WIDGET_H_


#include "graphwidget.h"


// 脉冲图控件
class WIDGET_EXPORT PulseWidget : public GraphWidget
{
    Q_OBJECT

public:
    PulseWidget(QWidget* parent = 0);
    virtual ~PulseWidget();

    // 清空直方图
    virtual void clear();

    // 显示选项
    void setShowGrid(bool showGrid);

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

protected:
    // 绘制图形
    virtual void drawGraph();

    // 刻度点
    virtual float scaleX(float x);
    virtual float scaleY(float y);

    // 图像点
    virtual float graphX(float x);
    virtual float graphY(float y);

private:
    // 绘制曲线
    virtual void drawCurve();

    // 绘制分类线
    virtual void drawLine();

    // 绘制背景线
    virtual void drawGrid();

    // 绘制刻度值
    virtual void drawScale();

    // 设置图形数据
    void setDataF(const QList<float>& datas);

    // 设置分类线数据
    void setLineF(const QList<float>& lines);

private:
    // 显示选项
    bool showGrid;

    // 图形数据
    QList<float> datas;
    QList<float> lines;
};


#endif // _PULSE_WIDGET_H_