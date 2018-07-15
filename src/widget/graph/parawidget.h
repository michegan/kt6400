#ifndef _PARA_WIDGET_H_
#define _PARA_WIDGET_H_


#include <QtGui/QWidget>

#include "para.h"
#include "libwidget.h"


// 参数控件
class WIDGET_EXPORT ParaWidget : public QWidget
{
    Q_OBJECT

public:
    ParaWidget(QWidget* parent = 0);
    virtual ~ParaWidget();

    // 行数
    void setRows(int rows);

    // 清空
    void clear();

    // 关联参数列表
    void setParas(const QStringList& paras);
    void setParaList(const ParaList& paraList);

protected:
    // 绘制事件
    virtual void paintEvent(QPaintEvent* event);

private:
    // 绘制内容
    virtual void drawContent();

    // 绘制背景
    virtual void drawBackground();

protected:
    // 行数
    int rows;

    // 参数列表
    ParaList paraList;
    QStringList paras;

    // 背景色（标题）
    QColor backgroundHead;
    // 背景色（内容，交替）
    QColor backgroundContent1;
    QColor backgroundContent2;

    // 前景色（标题）
    QColor foregroundHead;
    // 前景色（内容）
    QColor foregroundContent;
};


#endif // _PARA_WIDGET_H_