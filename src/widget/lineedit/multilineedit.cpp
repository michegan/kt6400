#include <QList>
#include <QHBoxLayout>
#include <QResizeEvent>

#include "digitlineedit.h"
#include "multilineedit.h"


MultiLineEdit::MultiLineEdit(int sections, const QString& spliter, QWidget* parent)
    : LineEdit(parent), sections(0), spliter("-")
{
    // 默认尺寸
    this->resize(100, 30);

    // 不具备焦点
    this->setFocusPolicy(Qt::NoFocus);

    // 分隔符
    this->spliter = spliter;
    // 分段数
    this->sections = sections;   

    // 创建子控件
    for (int i = 0; i < sections; i++)
    {
        // 编辑框
        DigitLineEdit* lineEdit = new DigitLineEdit(this);
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->installEventFilter(this);

        this->lineEdits.append(lineEdit);        

        // 分隔符
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

// 是否有效
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

// 尺寸变化
void MultiLineEdit::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width();
    int height = event->size().height();

    // 总字符数
    int digits = 0;
    foreach (DigitLineEdit* lineEdit, this->lineEdits)
    {
        digits += lineEdit->digits();
    }
    
    // 计算间隙
    QFontMetrics fm(this->font());
    float x_item = 1.0 * (width - 4) / (digits + 1);

    // 控件布局
    float x = 2;
    foreach (DigitLineEdit* lineEdit, this->lineEdits)
    {
        float w = lineEdit->digits() * x_item;
        lineEdit->setGeometry(x, 2, w, height - 4);

        x += w;
    }
}

// 事件过滤器
bool MultiLineEdit::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if (this->spliter == keyEvent->text())
        {
            // 当前焦点DigitLineEdit
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
            // 基类处理
            return LineEdit::eventFilter(obj, event);
        }
    }
    else
    {
        // 基类处理
        return LineEdit::eventFilter(obj, event);
    }
}

// 获取编辑框
DigitLineEdit* MultiLineEdit::lineEdit(int i)
{
    i *= 2;
    return (0 <= i && i < this->lineEdits.length() ? this->lineEdits.at(i) : 0);
}
