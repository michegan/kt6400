#ifndef _IP_LINEEDIT_H_
#define _IP_LINEEDIT_H_


#include "multilineedit.h"


// IPµØÖ·±à¼­¿ò¿Ø¼þ
class WIDGET_EXPORT IpLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    IpLineEdit(QWidget* parent = 0);
    virtual ~IpLineEdit();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};


#endif // _IP_LINEEDIT_H_