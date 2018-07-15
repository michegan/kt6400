#ifndef _LJ_QC_FILE_TABLE_WIDGET_H_
#define _LJ_QC_FILE_TABLE_WIDGET_H_


#include "tablewidget.h"

class LJQcFileTable;
class LJQcSampleTable;


// LJ质控文件表格控件
class LJQcFileTableWidget : public TableWidget
{
    Q_OBJECT

public:
    LJQcFileTableWidget(QWidget* parent = 0);
    virtual ~LJQcFileTableWidget();

    // 文件表
    void setLJQcFileTable(LJQcFileTable* fileTable);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // 文件表
    LJQcFileTable* fileTable;
};


#endif // _LJ_QC_FILE_TABLE_WIDGET_H_