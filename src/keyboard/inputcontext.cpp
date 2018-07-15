#include <QtDebug>
#include <QApplication>

#include "pinyin.h"
#include "proxystyle.h"
#include "inputcontext.h"
#include "digitkeyboard.h"
#include "frenchkeyboard.h"
#include "russiakeyboard.h"
#include "chinesekeyboard.h"
#include "englishkeyboard.h"
#include "spanishkeyboard.h"


class InputContextPrivate
{
public:
    InputContextPrivate();
    ~InputContextPrivate();

    // 资源初始化
    void resourceInit();

    // 键盘初始化
    void keyBoardInit();

    // 获取软键盘
    KeyBoard* getKeyBoard(QChar chr);

    // 控件对应的软键盘
    int widgetKeyBoard(QWidget* widget);

    // 更新当前软键盘
    void setKeyBoard(KeyBoard* keyBoard);

    // 调整软键盘显示位置
    void adjustKeyboardDisplayPosition(QWidget* pKeyBoard, QWidget* pEditWidget);

public:
    // 开关状态
    bool enabled;

    // 资源路径
    QString path;

    // 最大尺寸
    QSize maxSize;

    // 语言代码
    QString language;

    // 当前输入法
    PinYin* ime;

    // 当前键盘
    KeyBoard* keyBoard;

    // 小数点字符
    int decimalPointChar;

    // 键盘工厂
    QList<KeyBoard*> keyBoards;
};

InputContextPrivate::InputContextPrivate()
    : enabled(true), path(""), maxSize(800, 600), language("en-US"), ime(0), keyBoard(0), 
      decimalPointChar(Qt::Key_Period)
{

}

InputContextPrivate::~InputContextPrivate()
{
    if (this->ime)
    {
        delete this->ime;
    }
    
    if (this->keyBoard)
    {
        delete this->keyBoard;
    }
}

// 资源初始化
void InputContextPrivate::resourceInit()
{
    // 清空原输入法
    if (this->ime)
    {
        delete this->ime;
        this->ime = 0;
    }

    // 新输入法
    if (this->language.startsWith("zh-"))
    {
        // 汉语
        this->ime = new PinYin();
        this->ime->loadUser(this->path);
        this->ime->loadSystem(this->path);
    }
}

// 键盘初始化
void InputContextPrivate::keyBoardInit()
{
    // 清空原候选键盘
    foreach (KeyBoard* keyBoard, this->keyBoards)
    {
        delete keyBoard;
    }
    this->keyBoards.clear();

    // 创建新候选键盘
    if (this->language.startsWith("en-"))
    {
        // 英语

        // 字符键盘
        {
            EnglishMainKeyBoard* keyBoard = new EnglishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 数字键盘
        {
            EnglishNumberKeyBoard* keyBoard = new EnglishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 符号键盘
        {
            EnglishPunctionKeyBoard* keyBoard = new EnglishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("es-"))
    {
        // 西班牙语

        // 字符键盘
        {
            SpanishMainKeyBoard* keyBoard = new SpanishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 数字键盘
        {
            SpanishNumberKeyBoard* keyBoard = new SpanishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 符号键盘
        {
            SpanishPunctionKeyBoard* keyBoard = new SpanishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("zh-"))
    {
        // 汉语

        // 拼音键盘
        {
            // 汉语主软键盘（可切换到英文）
            ChineseMainKeyBoard* keyBoard = new ChineseMainKeyBoard();
            keyBoard->setIme(this->ime);
            this->keyBoards.append(keyBoard);
        }

        // 字符键盘
        {
            // 汉语字符软键盘（可切换到中文）
            ChineseLetter1KeyBoard* keyBoard1 = new ChineseLetter1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // 汉语字符软键盘（无中英文切换）
            ChineseLetter2KeyBoard* keyBoard2 = new ChineseLetter2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }

        // 数字键盘
        {
            // 汉语数字软键盘（可切换到英文）
            ChineseNumberKeyBoard* keyBoard = new ChineseNumberKeyBoard();
            this->keyBoards.append(keyBoard);

            // 汉语数字软键盘（可切换到中文）
            ChineseNumber1KeyBoard* keyBoard1 = new ChineseNumber1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // 汉语数字软键盘（无中英文切换）
            ChineseNumber2KeyBoard* keyBoard2 = new ChineseNumber2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }

        // 符号键盘
        {
            // 汉语符号软键盘（可切换到英文）
            ChinesePunctionKeyBoard* keyBoard = new ChinesePunctionKeyBoard();
            this->keyBoards.append(keyBoard);

            // 汉语符号软键盘（可切换到中文）
            ChinesePunction1KeyBoard* keyBoard1 = new ChinesePunction1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // 汉语符号软键盘（无中英文切换）
            ChinesePunction2KeyBoard* keyBoard2 = new ChinesePunction2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }
    }
    else if (this->language.startsWith("fr-"))
    {
        // 法语
        // 字符键盘
        {
            EnglishMainKeyBoard* keyBoard = new EnglishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 数字键盘
        {
            EnglishNumberKeyBoard* keyBoard = new EnglishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 符号键盘
        {
            EnglishPunctionKeyBoard* keyBoard = new EnglishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("ru-"))
    {
        // 俄语

        // 字符键盘
        {
            RussiaMainKeyBoard* keyBoard = new RussiaMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 数字键盘
        {
            RussiaNumberKeyBoard* keyBoard = new RussiaNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // 符号键盘
        {
            RussiaPunctionKeyBoard* keyBoard = new RussiaPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }

    // 数字键盘
    KeyBoard* keyBoard = new DigitKeyBoard(this->decimalPointChar);
    this->keyBoards.append(keyBoard);
}

// 获取软键盘
KeyBoard* InputContextPrivate::getKeyBoard(QChar chr)
{
    foreach (KeyBoard* keyBoard, this->keyBoards)
    {
        if (chr == keyBoard->id())
        {
            return keyBoard;
        }
    }
    return 0;
}

// 控件对应的软键盘
int InputContextPrivate::widgetKeyBoard(QWidget* widget)
{
    // 根据控件键盘动态属性决定关联何键盘
    QVariant variant = widget->property("SoftKeyBoard");
    if (variant.isValid())
    {
        QString softKeyBoard = variant.toString();
        if ("digit" == softKeyBoard)
        {
            // 关联数字键盘
            return Qt::Key_F10;
        }
        else if ("digit_full" == softKeyBoard)
        {
            if (this->language.startsWith("zh-"))
            {
                // 中文全数字软键盘（无中英文切换）
                return Qt::Key_F8;
            }
            else
            {
                // 全数字软键盘
                return Qt::Key_F2;
            }
        }
        else if ("character" == softKeyBoard)
        {
            if (this->language.startsWith("zh-"))
            {
                // 中文字符键盘
                return Qt::Key_F9;
            }
        }
    }

    // 多语言键盘
    return Qt::Key_F1;
}

// 更新当前软键盘
void InputContextPrivate::setKeyBoard(KeyBoard* keyBoard)
{
    if (this->keyBoard)
    {
        // 清除输入
        this->keyBoard->clear();

        // 隐藏当前软键盘
        this->keyBoard->hide();
    }

    if (keyBoard)
    {
        // 显示新的软键盘
        keyBoard->show();
    }

    // 更新当前软键盘
    this->keyBoard = keyBoard;
}

// 调整软键盘显示位置
void InputContextPrivate::adjustKeyboardDisplayPosition(QWidget* pKeyBoard, QWidget* pEditWidget)
{
    // 键盘尺寸
    int width = pKeyBoard->width();
    int height = pKeyBoard->height();

    // 主窗口尺寸
    int maxWidth = maxSize.width();
    int maxHeight = maxSize.height();

    // 编辑控件绝对位置
    QRect rect = pEditWidget->rect();
    QPoint topLeft = pEditWidget->mapToGlobal(rect.topLeft());
    QPoint bottomLeft = pEditWidget->mapToGlobal(rect.bottomLeft());
    QPoint bottomRight = pEditWidget->mapToGlobal(rect.bottomRight());
    int top = topLeft.y();
    int left = topLeft.x();
    int bottom = bottomLeft.y();

    // 软键盘位置定位
    int x = left;
    if (maxWidth <= left + width)
    {
        x = (maxWidth - width);
    }

    // 优先下部显示，否则上部显示
    int y = bottom;
    if (maxHeight <= bottom + height)
    {
        y = (top < height ? 0 : top - height);
    }

    // 软键盘位置定位
    pKeyBoard->move(x, y);

    // 上下移动后，需要在检测软键盘对编辑控件是否存在遮挡，若存在遮挡，则需要左右移动
    // 软键盘绝对位置
    QRect rectKb = pKeyBoard->rect();
    QPoint topLeftKb = pKeyBoard->mapToGlobal(rectKb.topLeft());
    QPoint bottomRightKb = pKeyBoard->mapToGlobal(rectKb.bottomRight());

    // 编辑控件和软键盘全局显示区域
    QRect editRectGlobal(topLeft, bottomRight);
    QRect keyboardRectGlobal(topLeftKb, bottomRightKb);

    // 检测软键盘和编辑控件是否存在重叠区域，存在，则横向调整软键盘显示位置
    if (keyboardRectGlobal.intersects(editRectGlobal))
    {
        QRect intersectRect = keyboardRectGlobal.intersected(editRectGlobal);
        
        // 较小的重叠区域，则直接忽略
        if (intersectRect.width() <= 5 || intersectRect.height() <= 5)
        {
            return;
        }

        // 右侧无法显示，则显示在左侧
        x = left + pEditWidget->width();
        if (maxWidth < x + width)
        {
            x = left > width ?  left - width : 0;
        }

        // 软键盘位置定位
        pKeyBoard->move(x, y);
    }
}


InputContext::InputContext(QObject* parent)
    : QInputContext(parent), d(new InputContextPrivate())
{
    qApp->installEventFilter(this);

    // 单击弹出软键盘
    qApp->setStyle(new ProxyStyle());
}

InputContext::~InputContext()
{
    delete d;
}

// 开关状态
bool InputContext::enabled() const
{
    return d->enabled;
}

void InputContext::setEnabled(bool enabled)
{
    d->enabled = enabled; 
    qDebug() << "InputContext setEnabled" << enabled;
}

// 资源路径
QString InputContext::rootPath()
{
    return d->path;
}

void InputContext::setRootPath(const QString& path)
{
    d->path = path;
    qDebug() << "InputContext setRootPath" << path;
}

// 语言代码
void InputContext::setLanguage(const QString& language)
{
    qDebug() << "InputContext setLanguage" << language;

    // 更新语言代码
    d->language = language;

    // 键盘初始化
    d->keyBoardInit();

    // 资源初始化
    d->resourceInit();  
}

// 设置小数点字符
void InputContext::setDecimalPointChar(int chr)
{
    // 删除原数字键盘
    KeyBoard* keyBoard = d->getKeyBoard(Qt::Key_F10);
    if (keyBoard)
    {        
        // 从软键盘列表中删除
        d->keyBoards.removeOne(keyBoard);

        // 释放内存
        delete keyBoard;
    }

    // 更新当前小数点字符
    d->decimalPointChar = chr;

    // 创建新的数字键盘
    keyBoard = new DigitKeyBoard(chr);
    if (keyBoard)
    {
        // 添加到软键盘列表
        d->keyBoards.append(keyBoard);
    }
}

// 加载用户词库
void InputContext::loadUserPhrase()
{
    // 加载用户词库
    if (d->ime)
    {
        d->ime->loadUser(d->path);
    }
}

// 最大尺寸
void InputContext::setMaxSize(const QSize& size)
{
    d->maxSize = size;
}

// 状态重置
void InputContext::reset()
{

}

// 语言代码
QString InputContext::language()
{
    return d->language;
}

// 是否组合
bool InputContext::isComposing() const
{
    return false;
}

// 标识
QString InputContext::identifierName()
{
    return "UNKNOWN";
}

// 事件处理
bool InputContext::filterEvent(const QEvent* event)
{
    int type = event->type();

    if (QEvent::CloseSoftwareInputPanel == type)
    {
        // 清空当前软键盘
        d->setKeyBoard(0);
    }
    else if (QEvent::RequestSoftwareInputPanel == type)
    {
        // 启用后才生效
        if (this->enabled())
        {
            QWidget* widget = this->focusWidget();
            if (widget)
            {
                // 焦点控件对应的键盘
                int chr = d->widgetKeyBoard(widget);

                // 切换到指定键盘
                this->switchToKeyBoard(chr);
            }
        }
    }

    return QInputContext::filterEvent(event);
}

// 过滤事件
bool InputContext::eventFilter(QObject *obj, QEvent *event)
{
    int type = event->type();

    if (type == QEvent::KeyPress) 
    {
        qDebug() << "InputContext eventFilter KeyPress";

        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // 拼音输入法反馈的字符串中的key值为 0 (在InputContext::onInputButtonClicked(const QString& text)函数中实现)，
        // 在此处将其排除，防止拼音输入法反馈的单字汉字，被再次作为输入，从而导致部分汉字无法输入
        if (keyEvent->text().length() == 1 && keyEvent->key() != 0)
        {
            QChar qCh = keyEvent->text().at(0);
            return this->onKeyReleaseEvent(qCh.toAscii());
        }
        else
        {
            return this->onKeyReleaseEvent(keyEvent->key());
        }
    }
    else if (type == QEvent::MouseButtonPress)
    {
        qDebug() << "InputContext eventFilter MouseButtonPress";

        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent)
        {
            this->onMouseButtonPressed(mouseEvent->globalPos());
        }
    }

    return QObject::eventFilter(obj, event);
}

// 按键处理
bool InputContext::onKeyReleaseEvent(int key)
{
    KeyBoard* keyBoard = d->keyBoard;

    // 交由当前键盘处理，是否处理取决于软键盘自身
    return (keyBoard ? keyBoard->onKeyReleaseEvent(key) : false);
}

// 鼠标点击
void InputContext::onMouseButtonPressed(const QPoint& globalPos)
{
    KeyBoard* keyBoard = d->keyBoard;

    // 是否有软键盘
    if (keyBoard)
    {
        // 是否显示软键盘
        if (keyBoard->isVisible())
        {
            // 用户点击区域是否在软键盘外部
            QRect rect = keyBoard->geometry();
            if (!rect.contains(globalPos))
            {
                // 清空当前软键盘
                d->setKeyBoard(0);
            }
        }
    }
}

// 切换到软键盘
void InputContext::switchToKeyBoard(int chr)
{
    // 当前软键盘
    KeyBoard* keyBoard = d->keyBoard;
    if (keyBoard)
    {
        // 断开信号槽
        this->disconnect(keyBoard, SIGNAL(clicked(int)), this, SLOT(onButtonClicked(int)));
        this->disconnect(keyBoard, SIGNAL(clicked(const QString&)), this, SLOT(onButtonClicked(const QString&)));

        // 清空当前软键盘
        d->setKeyBoard(0);
    }

    // 切换到新软键盘
    keyBoard = d->getKeyBoard(chr);
    if (keyBoard)
    {
        QWidget* widget = this->focusWidget();
        if (0 == widget)
        {
            return;
        }

        // 调整软键盘显示位置
        d->adjustKeyboardDisplayPosition(keyBoard, widget);

        // 关联信号槽
        this->connect(keyBoard, SIGNAL(clicked(int)), this, SLOT(onButtonClicked(int)), Qt::UniqueConnection);
        this->connect(keyBoard, SIGNAL(clicked(const QString&)), this, SLOT(onButtonClicked(const QString&)), Qt::UniqueConnection);

        // 转换为当前软键盘
        d->setKeyBoard(keyBoard);
    }
}

// 输入按键
void InputContext::onButtonClicked(int chr)
{
    if (Qt::Key_Close == chr)
    {
        // 关闭按键
        this->onCloseButtonClicked(chr);
    }
    else if (Qt::Key_Enter == chr)
    {
        // 回车按键
        // 客户需求：首先输入sample ID，出现软键盘，输入完点enter，这个时候这一项的输入已经完成了，软键盘应该自动关闭。
        //           我现在要输入第二项，我得在软键盘之外，sample对话框之内的小范围区域内点一下才能关闭软键盘。
        this->onCloseButtonClicked(chr);
    }
    else if (Qt::Key_CapsLock == chr)
    {
        // 大写锁定键

    }
    else if (Qt::Key_F1 <= chr && chr <= Qt::Key_F10)
    {
        // 输入按键
        this->onFunctionButtonClicked(chr);
    }
    else
    {
        // 输入按键
        this->onInputButtonClicked(chr);
    }
}

void InputContext::onButtonClicked(const QString& text)
{
    this->onInputButtonClicked(text);
}

// 关闭按键
void InputContext::onCloseButtonClicked(int chr)
{
    KeyBoard* keyBoard = d->keyBoard;
    if (keyBoard)
    {
        // 清空当前软键盘
        d->setKeyBoard(0);
    }
}

// 输入按键
void InputContext::onInputButtonClicked(int chr)
{
    // 焦点控件
    QWidget* widget = this->focusWidget();
    if (widget)
    {
        // 文本
        QString text = QChar(chr);
        if (d->keyBoard->capslock())
        {
            text = text.toUpper();
        }
        else
        {
            text = text.toLower();
        }

        // 按键按下
        QKeyEvent keyPress(QEvent::KeyPress, chr, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyPress);

        // 键盘释放
        QKeyEvent keyRelease(QEvent::KeyRelease, chr, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyRelease);
    }
}

void InputContext::onInputButtonClicked(const QString& text)
{
    // 焦点控件
    QWidget* widget = this->focusWidget();
    if (widget)
    {
        // 按键按下
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyPress);

        // 键盘释放
        QKeyEvent keyRelease(QEvent::KeyRelease, 0, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyRelease);
    }
}

// 功能按键
void InputContext::onFunctionButtonClicked(int chr)
{
    // 切换到目标键盘
    this->switchToKeyBoard(chr);
}