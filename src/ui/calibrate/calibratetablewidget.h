#ifndef _CALIBRATE_TABLE_WIDGET_H_
#define _CALIBRATE_TABLE_WIDGET_H_


#include "para.h"
#include "tablewidget.h"


// 校准表格控件
class CalibrateTableWidget : public TableWidget
{
    Q_OBJECT

public:
    CalibrateTableWidget(QWidget* parent = 0);
    virtual ~CalibrateTableWidget();

    // 表格内容
    void setContent(const QList<ParaList>& contents);

protected:
    // 获取表头内容
    virtual QStringList headText() const;

    // 获取表格内容
    virtual int numOfItems();
    virtual QStringList rowText(int row) const;

private:
    // 校准参数
    QStringList paraNames;

    // 首列列头
    QStringList vHeadText;

    // 表格内容
    QList<ParaList> contents;
};


#endif // _CALIBRATE_TABLE_WIDGET_H_