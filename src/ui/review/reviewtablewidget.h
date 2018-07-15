#ifndef _REVIEW_TABLE_WIDGET_H_
#define _REVIEW_TABLE_WIDGET_H_


#include "tablewidget.h"

class ReviewSampleTable;


// 回顾表格控件
class ReviewTableWidget : public TableWidget
{
    Q_OBJECT

public:
    ReviewTableWidget(QWidget* parent = 0);
    virtual ~ReviewTableWidget();

    // 设置起始索引
    void setFrom(int from);

    // 设置当前页样本
    void setSamples(const QList<int>& samples);

    // 样本表
    void setReviewSampleTable(ReviewSampleTable* sampleTable);

protected:
    // 选中模式（默认单选）
    bool isSingleSelect() const;

    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList columnText(int column);

private:
    // 起始索引
    int from;

    // 当前页样本
    QList<int> samples;

    // 样本表
    ReviewSampleTable* sampleTable;
};


#endif // _REVIEW_TABLE_WIDGET_H_