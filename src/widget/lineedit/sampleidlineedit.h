#ifndef _SAMPLE_ID_LINEEDIT_H_
#define _SAMPLE_ID_LINEEDIT_H_


#include "lineedit.h"

class SampleIdLineEditPrivate;


// 数字编辑框控件
class WIDGET_EXPORT SampleIdLineEdit : public LineEdit
{
    Q_OBJECT

public:
    SampleIdLineEdit(QWidget* parent = 0);
    virtual ~SampleIdLineEdit();

public:
    // 是否有效
    virtual bool isValid();

protected:
    // 按键响应
    virtual void keyPressEvent(QKeyEvent* event);

private:
    SampleIdLineEditPrivate* d;
};


#endif // _SAMPLE_ID_LINEEDIT_H_