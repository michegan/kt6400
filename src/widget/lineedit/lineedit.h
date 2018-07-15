#ifndef _LINEEDIT_H_
#define _LINEEDIT_H_


#include <QtGui/QLineEdit>

#include "libwidget.h"


// �༭��ؼ�
class WIDGET_EXPORT LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QWidget* parent = 0);
    virtual ~LineEdit();

    // �Ƿ���Ч
    virtual bool isValid();

protected:
    // ������Ӧ
    virtual void keyPressEvent(QKeyEvent* event);
};


#endif // _LINEEDIT_H_