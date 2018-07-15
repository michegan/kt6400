#ifndef _LJ_QC_TABLE_WIDGET_H_
#define _LJ_QC_TABLE_WIDGET_H_


#include "tablewidget.h"

class LJQcSampleTable;


// LJ质控表格控件
class LJQcTableWidget : public TableWidget
{
    Q_OBJECT

public:
    LJQcTableWidget(QWidget* parent = 0);
    virtual ~LJQcTableWidget();

    // 设置当前页样本
    void setSamples(const QList<int>& samples);

    // 样本表
    void setLJQcSampleTable(LJQcSampleTable* sampleTable);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList columnText(int columnNo);

private:
    // 当前页样本
    QList<int> samples;

    // 样本表
    LJQcSampleTable* sampleTable;
};


#endif // _LJ_QC_TABLE_WIDGET_H_