#include <QKeyEvent>
#include <QCoreApplication>

#include "iplineedit.h"
#include "digitlineedit.h"


// 分段数
#define NUM_OF_SECTIONS    (4)
#define NUM_RANGE_MAX      (255)
#define NUM_RANGE_MIN      (0)


IpLineEdit::IpLineEdit(QWidget* parent)
    : MultiLineEdit(NUM_OF_SECTIONS, ".", parent)
{
    // 默认尺寸
    this->resize(100, 30);

    // 设定格式，范围
    for (int i = 0; i < NUM_OF_SECTIONS; i++)
    {
        DigitLineEdit* lineEdit = this->lineEdit(i);
        if (lineEdit)
        {
            //lineEdit->setFormat(3, 0);
            lineEdit->setRange(NUM_RANGE_MIN, NUM_RANGE_MAX);
            lineEdit->installEventFilter(this);
        }
    }
}

IpLineEdit::~IpLineEdit()
{
}

bool IpLineEdit::eventFilter( QObject *obj, QEvent *event )
{
    if (obj->inherits("DigitLineEdit"))
    {
        if (event->type() == QEvent::KeyPress)
        {
            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(obj);
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key())
            {
            case Qt::Key_Period:
                {
                    if (!lineEdit->text().isEmpty())
                    {
                        QKeyEvent tabKey(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                        QCoreApplication::sendEvent(obj, &tabKey);
                    }
                }
                break;
                default:
                return MultiLineEdit::eventFilter(obj, event);
            }
            return true;
            }
            return false;
        }
    else
    {
        return MultiLineEdit::eventFilter(obj, event);
    }
}
