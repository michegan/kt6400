#include <QIcon>
#include <QBrush>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>

#include "resource.h"
#include "keybutton.h"


class KeyButtonPrivate
{
public:
    KeyButtonPrivate();
    ~KeyButtonPrivate();

public:
    // 字符
    int chr1;
    int chr2;

    // 是否显示字符
    bool showChr;

    // 背景
    QString image;
};

KeyButtonPrivate::KeyButtonPrivate()
    : chr1(0), chr2(0), showChr(true), image("")
{

}

KeyButtonPrivate::~KeyButtonPrivate()
{

}


KeyButton::KeyButton(QWidget* parent)
    : QPushButton(parent), d(new KeyButtonPrivate())
{
    this->setFocusPolicy(Qt::NoFocus);
}

KeyButton::~KeyButton()
{
    delete d;
}

// 字符
int KeyButton::chr1() const
{
    return d->chr1;
}

int KeyButton::chr2() const
{
    return d->chr2;
}

void KeyButton::setChr(int chr1, int chr2)
{
    d->chr1 = chr1;
    d->chr2 = chr2;

    update();
}

// 是否显示字符
bool KeyButton::showChr() const
{
    return d->showChr;
}

void KeyButton::setShowChr(bool showChr)
{
    d->showChr = showChr;

    update();
}

// 背景图
void KeyButton::setImage(const QString& image)
{
    d->image = image;

    update();
}

// 重绘事件
void KeyButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 根据按钮状态，确定背景图片
    QString swidth = QString::number(this->width());
    QString suffix = ((this->isDown() || this->isChecked()) ? "pressed" : "normal");

    // 绘制背景
    {
        QString key = d->image.isEmpty() ? "char" : d->image;
        QImage* image = Resource::image(key + "_" + swidth + "_" + suffix);

        if (image)
        {
            // 贴图
            painter.drawImage(this->rect(), *image);
        }
    }

    // 绘制前景
    if (!d->image.isEmpty())
    {
        QImage* image = Resource::image(d->image + "_" + swidth + "_" + suffix);
        if (image)
        {
            int x = (this->width() - image->width()) / 2;
            painter.drawImage(x, 0, *image);
        }
    }

    // 绘制文本
    if (d->showChr)
    {
        if (0 == d->chr1 && 0 == d->chr2)
        {
            // 无文本，不需要绘制
        }
        else if (0 != d->chr1 && 0 != d->chr2)
        {
            // 上下两个字符
            int height = this->height() / 2;

            QChar qchr1(d->chr1);
            if (qchr1.isPrint())
            {
                QRect rect(0, 0, this->width(), height);
                painter.drawText(rect, Qt::AlignCenter, QString(qchr1));
            }

            QChar qchr2(d->chr2);
            if (qchr2.isPrint())
            {
                QRect rect(0, height, this->width(), height);
                painter.drawText(rect, Qt::AlignCenter, QString(qchr2));
            }
        }
        else
        {
            int chr = (0 == d->chr1 ? d->chr2 : d->chr1);

            QChar qchr(chr);
            if (qchr.isPrint())
            {
                QRect rect = this->rect();
                painter.drawText(rect, Qt::AlignCenter, QString(qchr));
            }
        }
    }
}

// 双击事件
void KeyButton::mouseDoubleClickEvent(QMouseEvent* event)
{
    // 不响应此事件
    event->accept();
}