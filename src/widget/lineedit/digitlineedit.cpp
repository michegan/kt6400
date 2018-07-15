#include <qmath.h>
#include <QKeyEvent>

#include "digitlineedit.h"


DigitLineEdit::DigitLineEdit(QWidget* parent)
    : LineEdit(parent), lower(1), upper(99), integers(2), decimals(0)
{
    // Ĭ�ϳߴ�
    this->resize(100, 30);

    // Ĭ�����ּ���
    this->setProperty("SoftKeyBoard", "digit");
}

DigitLineEdit::~DigitLineEdit()
{

}

// ����ֵ
double DigitLineEdit::value() const
{
    QString text = this->text();

    if (text.isEmpty())
    {
        return -1;
    }
    else
    {
        bool ok = false;
        double value = text.toDouble(&ok);

        return (ok ? value : -1);
    }
}

void DigitLineEdit::setValue(double value)
{
    QString text = (0 <= value ? QString::number(value, 'f', this->decimals) : "");
    this->setText(text);
}

// ���÷�Χ
void DigitLineEdit::setRange(double lower, double upper)
{
    this->lower = lower;
    this->upper = upper;
}

// ���ø�ʽ
int DigitLineEdit::digits() const
{
    return (0 < this->decimals ? this->integers + this->decimals + 1 : this->integers);
}

void DigitLineEdit::setFormat(int integers, int decimals)
{
    this->integers = integers;
    this->decimals = decimals;

    // �༭����󳤶�
    this->setMaxLength(this->digits());
}

// �Ƿ���Ч
bool DigitLineEdit::isValid()
{
    QString text = this->text();

    // ��Ч�Լ��
    if (text.isEmpty())
    {
        return true;
    }
    else
    {
        bool ok = false;

        double value = text.toDouble(&ok);
        if (ok)
        {
            ok = (this->lower <= value && value <= this->upper);
        }
        return ok;
    }
    
}

// ������Ӧ
void DigitLineEdit::keyPressEvent(QKeyEvent* event)
{
    // ���ദ��
    LineEdit::keyPressEvent(event);

    // ���ദ��
    QString text = this->text();

    int key = event->key();
    switch (key)
    {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        {
            // �����������ּ�
        }
        break;

    case Qt::Key_Period:
        {
            // ��С���������Ѿ���С�����ˣ�ɾ����¼���С����
            if (0 == this->decimals)
            {
                backspace(); // û��С������
            }
            else
            {
                int num = text.count(key);
                if (num < 2)
                {
                    // ������С����
                }
                else
                {
                    backspace(); // ֻ����1��С����
                }
            }
        }
        break;

    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        {
            // ��Ӧ�˸����ɾ����
        }
        break;

    default:
        {
            backspace();
        }
        break;
    }
}