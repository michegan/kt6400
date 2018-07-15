#include <QList>
#include <QHBoxLayout>
#include <QResizeEvent>

#include "digitlineedit.h"
#include "multilineedit.h"


MultiLineEdit::MultiLineEdit(int sections, const QString& spliter, QWidget* parent)
    : LineEdit(parent), sections(0), spliter("-")
{
    // Ĭ�ϳߴ�
    this->resize(100, 30);

    // ���߱�����
    this->setFocusPolicy(Qt::NoFocus);

    // �ָ���
    this->spliter = spliter;
    // �ֶ���
    this->sections = sections;   

    // �����ӿؼ�
    for (int i = 0; i < sections; i++)
    {
        // �༭��
        DigitLineEdit* lineEdit = new DigitLineEdit(this);
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->installEventFilter(this);

        this->lineEdits.append(lineEdit);        

        // �ָ���
        if (i < sections - 1)
        {
            lineEdit = new DigitLineEdit(this);
            lineEdit->setText(spliter);
            lineEdit->setFrame(false);
            lineEdit->setFormat(spliter.length(), 0);
            lineEdit->setFocusPolicy(Qt::NoFocus);
            lineEdit->setAlignment(Qt::AlignCenter);

            this->lineEdits.append(lineEdit);
        }
    }
}

MultiLineEdit::~MultiLineEdit()
{

}

// �Ƿ���Ч
bool MultiLineEdit::isValid()
{
    for (int i = 0; i < this->lineEdits.length(); i += 2)
    {
        DigitLineEdit* lineEdit = this->lineEdits.at(i);

        if (!lineEdit->isValid())
        {
            return false;
        }
    }

    return true;
}

// �ߴ�仯
void MultiLineEdit::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width();
    int height = event->size().height();

    // ���ַ���
    int digits = 0;
    foreach (DigitLineEdit* lineEdit, this->lineEdits)
    {
        digits += lineEdit->digits();
    }
    
    // �����϶
    QFontMetrics fm(this->font());
    float x_item = 1.0 * (width - 4) / (digits + 1);

    // �ؼ�����
    float x = 2;
    foreach (DigitLineEdit* lineEdit, this->lineEdits)
    {
        float w = lineEdit->digits() * x_item;
        lineEdit->setGeometry(x, 2, w, height - 4);

        x += w;
    }
}

// �¼�������
bool MultiLineEdit::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if (this->spliter == keyEvent->text())
        {
            // ��ǰ����DigitLineEdit
            int length = this->lineEdits.length();
            for (int i = 0; i < length; i += 2)
            {
                if (this->lineEdit(i)->hasFocus())
                {
                    if (i < length - 2)
                    {
                        this->lineEdit(i + 2)->setFocus();
                        break;
                    }
                }
            }

            return true;
        }
        else
        {
            // ���ദ��
            return LineEdit::eventFilter(obj, event);
        }
    }
    else
    {
        // ���ദ��
        return LineEdit::eventFilter(obj, event);
    }
}

// ��ȡ�༭��
DigitLineEdit* MultiLineEdit::lineEdit(int i)
{
    i *= 2;
    return (0 <= i && i < this->lineEdits.length() ? this->lineEdits.at(i) : 0);
}
