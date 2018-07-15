#ifndef _PULSE_WIDGET_H_
#define _PULSE_WIDGET_H_


#include "graphwidget.h"


// ����ͼ�ؼ�
class WIDGET_EXPORT PulseWidget : public GraphWidget
{
    Q_OBJECT

public:
    PulseWidget(QWidget* parent = 0);
    virtual ~PulseWidget();

    // ���ֱ��ͼ
    virtual void clear();

    // ��ʾѡ��
    void setShowGrid(bool showGrid);

public:
    // ����ͼ������
    template<typename T>
    void setData(const QList<T>& datas)
    {
        // ת��Ϊfloat����
        QList<float> fdatas;
        foreach (T data, datas)
        {
            fdatas.append(data);
        }

        // ����ͼ������
        this->setDataF(fdatas);
    }

    template<typename T>
    void setData(const T* datas, int dataLen)
    {
        // ת��Ϊfloat����
        QList<float> fdatas;
        for (int i = 0; i < dataLen; i++)
        {
            fdatas.append(*(datas + i));
        }

        // ����ͼ������
        this->setDataF(fdatas);
    }

    // ���÷���������
    template<typename T>
    void setLine(const QList<T>& lines)
    {
        {
            // ת��Ϊfloat����
            QList<float> flines;
            foreach (T line, lines)
            {
                flines.append(line);
            }

            // ����ͼ������
            this->setLineF(flines);
        }
    }

    template<typename T>
    void setLine(const T* lines, int lineLen)
    {
        {
            // ת��Ϊfloat����
            QList<float> flines;
            for (int i = 0; i < lineLen; i++)
            {
                flines.append(*(lines + i));
            }

            // ����ͼ������
            this->setLineF(flines);
        }
    }

protected:
    // ����ͼ��
    virtual void drawGraph();

    // �̶ȵ�
    virtual float scaleX(float x);
    virtual float scaleY(float y);

    // ͼ���
    virtual float graphX(float x);
    virtual float graphY(float y);

private:
    // ��������
    virtual void drawCurve();

    // ���Ʒ�����
    virtual void drawLine();

    // ���Ʊ�����
    virtual void drawGrid();

    // ���ƿ̶�ֵ
    virtual void drawScale();

    // ����ͼ������
    void setDataF(const QList<float>& datas);

    // ���÷���������
    void setLineF(const QList<float>& lines);

private:
    // ��ʾѡ��
    bool showGrid;

    // ͼ������
    QList<float> datas;
    QList<float> lines;
};


#endif // _PULSE_WIDGET_H_