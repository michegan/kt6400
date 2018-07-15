#ifndef _HIST_WIDGET_H_
#define _HIST_WIDGET_H_


#include "graphwidget.h"


class HistInfo;
class HistWidgetPrivate;


// ֱ��ͼ
class WIDGET_EXPORT HistWidget : public GraphWidget
{
    Q_OBJECT

public:
    HistWidget(QWidget* parent = 0);
    virtual ~HistWidget();

    // ���ֱ��ͼ
    virtual void clear();

    // �Ƿ�ɱ༭
    void setEditable(bool editable);

    // �������
    void setFillHist(bool fillHist);

    // ����ֱ��ͼ��Ϣ
    void setHistInfo(const HistInfo& histInfo);

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

signals:
    // �����
    void clicked();

protected:
    // �����¼�
    virtual void keyPressEvent(QKeyEvent* event);

    // ����¼�
    virtual void mousePressEvent(QMouseEvent* event);

protected:
    // ����ͼ��
    virtual void drawGraph();

    // �̶ȵ�
    virtual float scaleX(float x);

    // ͼ���
    virtual float graphX(float x);
    virtual float graphY(float y);

private:
    // ����ֱ��ͼ
    virtual void drawHist();

    // ���Ʒ�����
    virtual void drawLine();

    // ���ƿ̶�ֵ
    virtual void drawScale();

    // ����ͼ������
    void setDataF(const QList<float>& datas);

    // ���÷���������
    void setLineF(const QList<float>& lines);

private:
    HistWidgetPrivate* d;
};


// WBCֱ��ͼ:
class WIDGET_EXPORT WbcHistWidget : public HistWidget
{
    Q_OBJECT

public:
    WbcHistWidget(QWidget* parent = 0);
    virtual ~WbcHistWidget();
};


// RBCֱ��ͼ
class WIDGET_EXPORT RbcHistWidget : public HistWidget
{
    Q_OBJECT

public:
    RbcHistWidget(QWidget* parent = 0);
    virtual ~RbcHistWidget();
};


// PLTֱ��ͼ
class WIDGET_EXPORT PltHistWidget : public HistWidget
{
    Q_OBJECT

public:
    PltHistWidget(QWidget* parent = 0);
    virtual ~PltHistWidget();
};


#endif // _HIST_WIDGET_H_