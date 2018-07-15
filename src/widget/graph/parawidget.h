#ifndef _PARA_WIDGET_H_
#define _PARA_WIDGET_H_


#include <QtGui/QWidget>

#include "para.h"
#include "libwidget.h"


// �����ؼ�
class WIDGET_EXPORT ParaWidget : public QWidget
{
    Q_OBJECT

public:
    ParaWidget(QWidget* parent = 0);
    virtual ~ParaWidget();

    // ����
    void setRows(int rows);

    // ���
    void clear();

    // ���������б�
    void setParas(const QStringList& paras);
    void setParaList(const ParaList& paraList);

protected:
    // �����¼�
    virtual void paintEvent(QPaintEvent* event);

private:
    // ��������
    virtual void drawContent();

    // ���Ʊ���
    virtual void drawBackground();

protected:
    // ����
    int rows;

    // �����б�
    ParaList paraList;
    QStringList paras;

    // ����ɫ�����⣩
    QColor backgroundHead;
    // ����ɫ�����ݣ����棩
    QColor backgroundContent1;
    QColor backgroundContent2;

    // ǰ��ɫ�����⣩
    QColor foregroundHead;
    // ǰ��ɫ�����ݣ�
    QColor foregroundContent;
};


#endif // _PARA_WIDGET_H_