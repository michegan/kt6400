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
    // �ַ�
    int chr1;
    int chr2;

    // �Ƿ���ʾ�ַ�
    bool showChr;

    // ����
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

// �ַ�
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

// �Ƿ���ʾ�ַ�
bool KeyButton::showChr() const
{
    return d->showChr;
}

void KeyButton::setShowChr(bool showChr)
{
    d->showChr = showChr;

    update();
}

// ����ͼ
void KeyButton::setImage(const QString& image)
{
    d->image = image;

    update();
}

// �ػ��¼�
void KeyButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // ���ݰ�ť״̬��ȷ������ͼƬ
    QString swidth = QString::number(this->width());
    QString suffix = ((this->isDown() || this->isChecked()) ? "pressed" : "normal");

    // ���Ʊ���
    {
        QString key = d->image.isEmpty() ? "char" : d->image;
        QImage* image = Resource::image(key + "_" + swidth + "_" + suffix);

        if (image)
        {
            // ��ͼ
            painter.drawImage(this->rect(), *image);
        }
    }

    // ����ǰ��
    if (!d->image.isEmpty())
    {
        QImage* image = Resource::image(d->image + "_" + swidth + "_" + suffix);
        if (image)
        {
            int x = (this->width() - image->width()) / 2;
            painter.drawImage(x, 0, *image);
        }
    }

    // �����ı�
    if (d->showChr)
    {
        if (0 == d->chr1 && 0 == d->chr2)
        {
            // ���ı�������Ҫ����
        }
        else if (0 != d->chr1 && 0 != d->chr2)
        {
            // ���������ַ�
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

// ˫���¼�
void KeyButton::mouseDoubleClickEvent(QMouseEvent* event)
{
    // ����Ӧ���¼�
    event->accept();
}