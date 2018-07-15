#ifndef _MULTI_LINEEDIT_H_
#define _MULTI_LINEEDIT_H_


#include "lineedit.h"

class DigitLineEdit;


// ��α༭��ؼ�
class WIDGET_EXPORT MultiLineEdit : public LineEdit
{
    Q_OBJECT

public:
    MultiLineEdit(int sections, const QString& spliter, QWidget* parent = 0);
    virtual ~MultiLineEdit();

    // �Ƿ���Ч
    virtual bool isValid();

protected:
    // �ߴ�仯
    virtual void resizeEvent(QResizeEvent* event);

    // �¼�������
    virtual bool eventFilter(QObject* obj, QEvent* event);

protected:
    // ��ȡ�༭��
    DigitLineEdit* lineEdit(int i);

private:
    // �ֶ���
    int sections;
    // �ָ���
    QString spliter;

    // �ӱ༭��
    QList<DigitLineEdit*> lineEdits;
};


#endif // _MULTI_LINEEDIT_H_