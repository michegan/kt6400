#ifndef _MULTI_LINEEDIT_H_
#define _MULTI_LINEEDIT_H_


#include "lineedit.h"

class DigitLineEdit;


// 多段编辑框控件
class WIDGET_EXPORT MultiLineEdit : public LineEdit
{
    Q_OBJECT

public:
    MultiLineEdit(int sections, const QString& spliter, QWidget* parent = 0);
    virtual ~MultiLineEdit();

    // 是否有效
    virtual bool isValid();

protected:
    // 尺寸变化
    virtual void resizeEvent(QResizeEvent* event);

    // 事件过滤器
    virtual bool eventFilter(QObject* obj, QEvent* event);

protected:
    // 获取编辑框
    DigitLineEdit* lineEdit(int i);

private:
    // 分段数
    int sections;
    // 分隔符
    QString spliter;

    // 子编辑框
    QList<DigitLineEdit*> lineEdits;
};


#endif // _MULTI_LINEEDIT_H_