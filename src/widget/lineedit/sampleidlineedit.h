#ifndef _SAMPLE_ID_LINEEDIT_H_
#define _SAMPLE_ID_LINEEDIT_H_


#include "lineedit.h"

class SampleIdLineEditPrivate;


// ���ֱ༭��ؼ�
class WIDGET_EXPORT SampleIdLineEdit : public LineEdit
{
    Q_OBJECT

public:
    SampleIdLineEdit(QWidget* parent = 0);
    virtual ~SampleIdLineEdit();

public:
    // �Ƿ���Ч
    virtual bool isValid();

protected:
    // ������Ӧ
    virtual void keyPressEvent(QKeyEvent* event);

private:
    SampleIdLineEditPrivate* d;
};


#endif // _SAMPLE_ID_LINEEDIT_H_