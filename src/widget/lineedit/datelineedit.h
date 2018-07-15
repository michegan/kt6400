#ifndef _DATE_LINEEDIT_H_
#define _DATE_LINEEDIT_H_


#include <QDate>

#include "multilineedit.h"


// ���ڱ༭��ؼ�
class WIDGET_EXPORT DateLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    DateLineEdit(QWidget* parent = 0);
    virtual ~DateLineEdit();

    // ��Ч��
    bool isNull();
    bool isValid();

    // ����
    QDate date();
    void setDate(const QDate& date);

    // ���ڸ�ʽ
    void setDateFormat(const QString& format);

private:
    // ����
    int year();
    int month();
    int day();

    // ���ڿؼ�
    DigitLineEdit* yearEdit();
    DigitLineEdit* monthEdit();
    DigitLineEdit* dayEdit();

private:
    // ���ڸ�ʽ
    QString format;
};


#endif // _DATE_LINEEDIT_H_