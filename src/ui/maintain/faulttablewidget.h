#ifndef _FAULT_TABLE_WIDGET_H_
#define _FAULT_TABLE_WIDGET_H_


#include "para.h"
#include "tablewidget.h"


// 故障表格控件
class FaultTableWidget : public TableWidget
{
    Q_OBJECT

public:
    FaultTableWidget(QWidget* parent = 0);
    virtual ~FaultTableWidget();

    // 故障列表
    void setFaults(const QList<int>& faults);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // 故障列表
    QList<int> faults;

    // 故障描述
    QStringList faultIds;
};


#endif // _FAULT_TABLE_WIDGET_H_