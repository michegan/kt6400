#ifndef _UNIT_WIDGET_H_
#define _UNIT_WIDGET_H_


#include "parawidget.h"


// ��λ�ؼ�
class WIDGET_EXPORT UnitWidget : public ParaWidget
{
    Q_OBJECT

public:
    UnitWidget(QWidget* parent = 0);
    virtual ~UnitWidget();

private:
    // ��������
    virtual void drawContent();
};


#endif // _UNIT_WIDGET_H_