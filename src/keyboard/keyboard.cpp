#include <QList>
#include <QImage>
#include <QtDebug>
#include <QSignalMapper>

#include "keyboard.h"
#include "keybutton.h"


// 内部间距
#define X_SPACE        8
#define Y_SPACE        8

// 外部边距
#define X_MARGIN       10
#define Y_MAIGIN       10

// 按钮高度
#define BUTTON_HEIGHT  43


class KeyBoardPrivate
{
public:
    KeyBoardPrivate(KeyBoard* p);
    ~KeyBoardPrivate();

    // 新按键
    KeyButton* newButton(int width);

    // 获取字符键键值
    int getCharKeyValue(int chr, bool bCapslock);

private:
    // 新按钮位置
    QPoint newButtonPos();

public:
    // 标识
    int id;

    // 键盘
    KeyBoard* q;

    // 界面风格
    int xspace;
    int yspace;
    int xmargin;
    int ymargin;

    // 按键列表
    QList<KeyButton*> buttons;

    // 按键响应
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

// 添加按键
KeyButton* KeyBoardPrivate::newButton(int width)
{
    KeyButton* button = new KeyButton(q);
    if (button)
    {
        // 计算按钮位置
        QPoint pos = this->newButtonPos();
        // 调整按钮位置
        button->setGeometry(pos.x(), pos.y(), width, BUTTON_HEIGHT);
    }
    return button;
}

// 获取字符键键值
int KeyBoardPrivate::getCharKeyValue(int chr, bool bCapslock)
{
    int iKeyValue = 0;
    QChar qChr(chr);

    // 根据capslock键的按下状态获取其键值
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

// 新按钮位置
QPoint KeyBoardPrivate::newButtonPos()
{
    int lines = this->buttons.count(0);
    int lastLine = this->buttons.lastIndexOf(0);

    // 计算新按钮位置
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
    // 标识
    d->id = id;

    // 不活的焦点
    this->setFocusPolicy(Qt::NoFocus);

    // 背景色
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xc5, 0xc8, 0xce));
    this->setPalette(palette);

    // 关联信号槽
    this->connect(d->signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(onSignalMapped(QWidget*)));
}

KeyBoard::~KeyBoard()
{
    delete d;
}

// 标识
int KeyBoard::id() const
{
    return d->id;
}

// 界面风格
void KeyBoard::setYSpace(int space)
{
    d->yspace = space;
}

void KeyBoard::setYMargin(int margin)
{
    d->ymargin = margin;
}

// CAPS状态
bool KeyBoard::capslock() const
{
    KeyButton* button = this->button(Qt::Key_CapsLock);
    return (button ? button->isChecked() : false);
}

// 清除输入
void KeyBoard::clear()
{
    KeyButton* button = this->button(Qt::Key_CapsLock);
    if (button)
    {
        button->setChecked(false);
    }
}

// 按键处理
bool KeyBoard::onKeyReleaseEvent(int key)
{
    return false;
}

// 换行
void KeyBoard::newLine(int x)
{
    d->xmargin = x;

    // 非首行，则添加换行标记
    if (!d->buttons.isEmpty())
    {
        d->buttons.append(0);
    }
}

// 按钮
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

// 添加字符按键
void KeyBoard::addChrButton(int chr1, int chr2, int width)
{
    KeyButton* button = d->newButton(width);
    if (button)
    {
        // 按钮属性，根据当前软键盘大小写锁定状态，添加软键盘字符显示
        bool bCapslock = capslock();
        button->setChr(d->getCharKeyValue(chr1, bCapslock), d->getCharKeyValue(chr2, bCapslock));
        button->setShowChr(true);

        // 添加按键
        this->addButton(button);
    }
}

// 添加图片按键
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

        // 添加按键
        this->addButton(button);

        // 大小写锁定键
        if (Qt::Key_CapsLock == chr1)
        {
            // 关联大小写锁定按钮是否按下信号，以便于处理软键盘中字符的大小写刷新显示
            connect(button, SIGNAL(toggled(bool)), SLOT(onCapslockBtnChecked(bool)));
        }
    }
}

// 信号映射
void KeyBoard::onSignalMapped(QWidget* widget)
{
    KeyButton* keyButton = dynamic_cast<KeyButton*>(widget);
    if (keyButton)
    {
        int chr1 = keyButton->chr1();
        int chr2 = keyButton->chr2();
        int chr = (0 == chr2 ? chr1 : chr2);

        // 发送信号
        emit clicked(chr);
    }
}

// 大小写锁定处理
void KeyBoard::onCapslockBtnChecked(bool bChecked)
{
    // 遍历软键盘中的所有按键
    foreach (KeyButton* pBtn, d->buttons)
    {
        if (pBtn)
        {
            // 只对字符按键进行大小写切换处理
            int iCharKeyValue = pBtn->chr1();
            QChar btnCh(iCharKeyValue);
            if (btnCh.isLetter())
            {
                pBtn->setChr(d->getCharKeyValue(iCharKeyValue, bChecked));
            }
        }   
    }
}

// 添加按钮
void KeyBoard::addButton(KeyButton* button)
{
    // 添加按钮
    d->buttons.append(button);

    // 按钮响应
    d->signalMapper->setMapping(button, button);
    this->connect(button, SIGNAL(clicked()), d->signalMapper, SLOT(map()));
}