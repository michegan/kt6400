#ifndef _UNIT_WIDGET_H_
#define _UNIT_WIDGET_H_


#include "parawidget.h"


// 单位控件
class WIDGET_EXPORT UnitWidget : public ParaWidget
{
    Q_OBJECT

public:
    UnitWidget(QWidget* parent = 0);
    virtual ~UnitWidget();

private:
    // 绘制内容
    virtual void drawContent();
};


#endif // _UNIT_WIDGET_H_