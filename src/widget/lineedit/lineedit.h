#ifndef _LINEEDIT_H_
#define _LINEEDIT_H_


#include <QtGui/QLineEdit>

#include "libwidget.h"


// 编辑框控件
class WIDGET_EXPORT LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QWidget* parent = 0);
    virtual ~LineEdit();

    // 是否有效
    virtual bool isValid();

protected:
    // 按键响应
    virtual void keyPressEvent(QKeyEvent* event);
};


#endif // _LINEEDIT_H_