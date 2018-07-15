#include <QList>
#include <QImage>
#include <QtDebug>
#include <QSignalMapper>

#include "keyboard.h"
#include "keybutton.h"


// �ڲ����
#define X_SPACE        8
#define Y_SPACE        8

// �ⲿ�߾�
#define X_MARGIN       10
#define Y_MAIGIN       10

// ��ť�߶�
#define BUTTON_HEIGHT  43


class KeyBoardPrivate
{
public:
    KeyBoardPrivate(KeyBoard* p);
    ~KeyBoardPrivate();

    // �°���
    KeyButton* newButton(int width);

    // ��ȡ�ַ�����ֵ
    int getCharKeyValue(int chr, bool bCapslock);

private:
    // �°�ťλ��
    QPoint newButtonPos();

public:
    // ��ʶ
    int id;

    // ����
    KeyBoard* q;

    // ������
    int xspace;
    int yspace;
    int xmargin;
    int ymargin;

    // �����б�
    QList<KeyButton*> buttons;

    // ������Ӧ
    QSignalMapper* signalMapper;
};

KeyBoardPrivate::KeyBoardPrivate(KeyBoard* p)
    : id(), q(p), xspace(X_SPACE), yspace(Y_SPACE), xmargin(X_MARGIN), ymargin(Y_MAIGIN), signalMapper(new QSignalMapper())
{

}

KeyBoardPrivate::~KeyBoardPrivate()
{
    delete signalMapper;
}

// ��Ӱ���
KeyButton* KeyBoardPrivate::newButton(int width)
{
    KeyButton* button = new KeyButton(q);
    if (button)
    {
        // ���㰴ťλ��
        QPoint pos = this->newButtonPos();
        // ������ťλ��
        button->setGeometry(pos.x(), pos.y(), width, BUTTON_HEIGHT);
    }
    return button;
}

// ��ȡ�ַ�����ֵ
int KeyBoardPrivate::getCharKeyValue(int chr, bool bCapslock)
{
    int iKeyValue = 0;
    QChar qChr(chr);

    // ����capslock���İ���״̬��ȡ���ֵ
    if (bCapslock)
    {
        iKeyValue = qChr.toUpper().unicode();
    }
    else
    {
        iKeyValue = qChr.toLower().unicode();
    }

    return iKeyValue;
}

// �°�ťλ��
QPoint KeyBoardPrivate::newButtonPos()
{
    int lines = this->buttons.count(0);
    int lastLine = this->buttons.lastIndexOf(0);

    // �����°�ťλ��
    int x = this->xmargin;
    for (int i = qMax<int>(0, lastLine); i < buttons.size(); i++)
    {
        KeyButton* button = this->buttons.at(i);
        if (button)
        {
            x += button->width();
            x += this->xspace;
        }
    }

    int y = this->ymargin;
    for (int i = 0; i < lines; i++)
    {
        y += BUTTON_HEIGHT;
        y += this->yspace;
    }

    return QPoint(x, y);
}


KeyBoard::KeyBoard(int id)
    : QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint), d(new KeyBoardPrivate(this))
{
    // ��ʶ
    d->id = id;

    // ����Ľ���
    this->setFocusPolicy(Qt::NoFocus);

    // ����ɫ
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xc5, 0xc8, 0xce));
    this->setPalette(palette);

    // �����źŲ�
    this->connect(d->signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(onSignalMapped(QWidget*)));
}

KeyBoard::~KeyBoard()
{
    delete d;
}

// ��ʶ
int KeyBoard::id() const
{
    return d->id;
}

// ������
void KeyBoard::setYSpace(int space)
{
    d->yspace = space;
}

void KeyBoard::setYMargin(int margin)
{
    d->ymargin = margin;
}

// CAPS״̬
bool KeyBoard::capslock() const
{
    KeyButton* button = this->button(Qt::Key_CapsLock);
    return (button ? button->isChecked() : false);
}

// �������
void KeyBoard::clear()
{
    KeyButton* button = this->button(Qt::Key_CapsLock);
    if (button)
    {
        button->setChecked(false);
    }
}

// ��������
bool KeyBoard::onKeyReleaseEvent(int key)
{
    return false;
}

// ����
void KeyBoard::newLine(int x)
{
    d->xmargin = x;

    // �����У�����ӻ��б��
    if (!d->buttons.isEmpty())
    {
        d->buttons.append(0);
    }
}

// ��ť
KeyButton* KeyBoard::button(int chr1) const
{
    foreach (KeyButton* button, d->buttons)
    {
        if (button && (chr1 == button->chr1()))
        {
            return button;
        }
    }
    return 0;
}

// ����ַ�����
void KeyBoard::addChrButton(int chr1, int chr2, int width)
{
    KeyButton* button = d->newButton(width);
    if (button)
    {
        // ��ť���ԣ����ݵ�ǰ����̴�Сд����״̬�����������ַ���ʾ
        bool bCapslock = capslock();
        button->setChr(d->getCharKeyValue(chr1, bCapslock), d->getCharKeyValue(chr2, bCapslock));
        button->setShowChr(true);

        // ��Ӱ���
        this->addButton(button);
    }
}

// ���ͼƬ����
void KeyBoard::addImageButton(const QString& image, int width, bool showChr)
{
    this->addImageButton(0, image, width, showChr);
}

void KeyBoard::addImageButton(int chr1, const QString& image, int width, bool showChr)
{
    KeyButton* button = d->newButton(width);
    if (button)
    {
        button->setChr(chr1);
        button->setImage(image);
        button->setShowChr(showChr);

        // ��Ӱ���
        this->addButton(button);

        // ��Сд������
        if (Qt::Key_CapsLock == chr1)
        {
            // ������Сд������ť�Ƿ����źţ��Ա��ڴ�����������ַ��Ĵ�Сдˢ����ʾ
            connect(button, SIGNAL(toggled(bool)), SLOT(onCapslockBtnChecked(bool)));
        }
    }
}

// �ź�ӳ��
void KeyBoard::onSignalMapped(QWidget* widget)
{
    KeyButton* keyButton = dynamic_cast<KeyButton*>(widget);
    if (keyButton)
    {
        int chr1 = keyButton->chr1();
        int chr2 = keyButton->chr2();
        int chr = (0 == chr2 ? chr1 : chr2);

        // �����ź�
        emit clicked(chr);
    }
}

// ��Сд��������
void KeyBoard::onCapslockBtnChecked(bool bChecked)
{
    // ����������е����а���
    foreach (KeyButton* pBtn, d->buttons)
    {
        if (pBtn)
        {
            // ֻ���ַ��������д�Сд�л�����
            int iCharKeyValue = pBtn->chr1();
            QChar btnCh(iCharKeyValue);
            if (btnCh.isLetter())
            {
                pBtn->setChr(d->getCharKeyValue(iCharKeyValue, bChecked));
            }
        }   
    }
}

// ��Ӱ�ť
void KeyBoard::addButton(KeyButton* button)
{
    // ��Ӱ�ť
    d->buttons.append(button);

    // ��ť��Ӧ
    d->signalMapper->setMapping(button, button);
    this->connect(button, SIGNAL(clicked()), d->signalMapper, SLOT(map()));
}