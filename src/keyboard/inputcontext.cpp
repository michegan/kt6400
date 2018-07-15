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

    // ��Դ��ʼ��
    void resourceInit();

    // ���̳�ʼ��
    void keyBoardInit();

    // ��ȡ�����
    KeyBoard* getKeyBoard(QChar chr);

    // �ؼ���Ӧ�������
    int widgetKeyBoard(QWidget* widget);

    // ���µ�ǰ�����
    void setKeyBoard(KeyBoard* keyBoard);

    // �����������ʾλ��
    void adjustKeyboardDisplayPosition(QWidget* pKeyBoard, QWidget* pEditWidget);

public:
    // ����״̬
    bool enabled;

    // ��Դ·��
    QString path;

    // ���ߴ�
    QSize maxSize;

    // ���Դ���
    QString language;

    // ��ǰ���뷨
    PinYin* ime;

    // ��ǰ����
    KeyBoard* keyBoard;

    // С�����ַ�
    int decimalPointChar;

    // ���̹���
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

// ��Դ��ʼ��
void InputContextPrivate::resourceInit()
{
    // ���ԭ���뷨
    if (this->ime)
    {
        delete this->ime;
        this->ime = 0;
    }

    // �����뷨
    if (this->language.startsWith("zh-"))
    {
        // ����
        this->ime = new PinYin();
        this->ime->loadUser(this->path);
        this->ime->loadSystem(this->path);
    }
}

// ���̳�ʼ��
void InputContextPrivate::keyBoardInit()
{
    // ���ԭ��ѡ����
    foreach (KeyBoard* keyBoard, this->keyBoards)
    {
        delete keyBoard;
    }
    this->keyBoards.clear();

    // �����º�ѡ����
    if (this->language.startsWith("en-"))
    {
        // Ӣ��

        // �ַ�����
        {
            EnglishMainKeyBoard* keyBoard = new EnglishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ּ���
        {
            EnglishNumberKeyBoard* keyBoard = new EnglishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ż���
        {
            EnglishPunctionKeyBoard* keyBoard = new EnglishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("es-"))
    {
        // ��������

        // �ַ�����
        {
            SpanishMainKeyBoard* keyBoard = new SpanishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ּ���
        {
            SpanishNumberKeyBoard* keyBoard = new SpanishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ż���
        {
            SpanishPunctionKeyBoard* keyBoard = new SpanishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("zh-"))
    {
        // ����

        // ƴ������
        {
            // ����������̣����л���Ӣ�ģ�
            ChineseMainKeyBoard* keyBoard = new ChineseMainKeyBoard();
            keyBoard->setIme(this->ime);
            this->keyBoards.append(keyBoard);
        }

        // �ַ�����
        {
            // �����ַ�����̣����л������ģ�
            ChineseLetter1KeyBoard* keyBoard1 = new ChineseLetter1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // �����ַ�����̣�����Ӣ���л���
            ChineseLetter2KeyBoard* keyBoard2 = new ChineseLetter2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }

        // ���ּ���
        {
            // ������������̣����л���Ӣ�ģ�
            ChineseNumberKeyBoard* keyBoard = new ChineseNumberKeyBoard();
            this->keyBoards.append(keyBoard);

            // ������������̣����л������ģ�
            ChineseNumber1KeyBoard* keyBoard1 = new ChineseNumber1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // ������������̣�����Ӣ���л���
            ChineseNumber2KeyBoard* keyBoard2 = new ChineseNumber2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }

        // ���ż���
        {
            // �����������̣����л���Ӣ�ģ�
            ChinesePunctionKeyBoard* keyBoard = new ChinesePunctionKeyBoard();
            this->keyBoards.append(keyBoard);

            // �����������̣����л������ģ�
            ChinesePunction1KeyBoard* keyBoard1 = new ChinesePunction1KeyBoard();
            this->keyBoards.append(keyBoard1);

            // �����������̣�����Ӣ���л���
            ChinesePunction2KeyBoard* keyBoard2 = new ChinesePunction2KeyBoard();
            this->keyBoards.append(keyBoard2);
        }
    }
    else if (this->language.startsWith("fr-"))
    {
        // ����
        // �ַ�����
        {
            EnglishMainKeyBoard* keyBoard = new EnglishMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ּ���
        {
            EnglishNumberKeyBoard* keyBoard = new EnglishNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ż���
        {
            EnglishPunctionKeyBoard* keyBoard = new EnglishPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }
    else if (this->language.startsWith("ru-"))
    {
        // ����

        // �ַ�����
        {
            RussiaMainKeyBoard* keyBoard = new RussiaMainKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ּ���
        {
            RussiaNumberKeyBoard* keyBoard = new RussiaNumberKeyBoard();
            this->keyBoards.append(keyBoard);
        }

        // ���ż���
        {
            RussiaPunctionKeyBoard* keyBoard = new RussiaPunctionKeyBoard();
            this->keyBoards.append(keyBoard);
        }
    }

    // ���ּ���
    KeyBoard* keyBoard = new DigitKeyBoard(this->decimalPointChar);
    this->keyBoards.append(keyBoard);
}

// ��ȡ�����
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

// �ؼ���Ӧ�������
int InputContextPrivate::widgetKeyBoard(QWidget* widget)
{
    // ���ݿؼ����̶�̬���Ծ��������μ���
    QVariant variant = widget->property("SoftKeyBoard");
    if (variant.isValid())
    {
        QString softKeyBoard = variant.toString();
        if ("digit" == softKeyBoard)
        {
            // �������ּ���
            return Qt::Key_F10;
        }
        else if ("digit_full" == softKeyBoard)
        {
            if (this->language.startsWith("zh-"))
            {
                // ����ȫ��������̣�����Ӣ���л���
                return Qt::Key_F8;
            }
            else
            {
                // ȫ���������
                return Qt::Key_F2;
            }
        }
        else if ("character" == softKeyBoard)
        {
            if (this->language.startsWith("zh-"))
            {
                // �����ַ�����
                return Qt::Key_F9;
            }
        }
    }

    // �����Լ���
    return Qt::Key_F1;
}

// ���µ�ǰ�����
void InputContextPrivate::setKeyBoard(KeyBoard* keyBoard)
{
    if (this->keyBoard)
    {
        // �������
        this->keyBoard->clear();

        // ���ص�ǰ�����
        this->keyBoard->hide();
    }

    if (keyBoard)
    {
        // ��ʾ�µ������
        keyBoard->show();
    }

    // ���µ�ǰ�����
    this->keyBoard = keyBoard;
}

// �����������ʾλ��
void InputContextPrivate::adjustKeyboardDisplayPosition(QWidget* pKeyBoard, QWidget* pEditWidget)
{
    // ���̳ߴ�
    int width = pKeyBoard->width();
    int height = pKeyBoard->height();

    // �����ڳߴ�
    int maxWidth = maxSize.width();
    int maxHeight = maxSize.height();

    // �༭�ؼ�����λ��
    QRect rect = pEditWidget->rect();
    QPoint topLeft = pEditWidget->mapToGlobal(rect.topLeft());
    QPoint bottomLeft = pEditWidget->mapToGlobal(rect.bottomLeft());
    QPoint bottomRight = pEditWidget->mapToGlobal(rect.bottomRight());
    int top = topLeft.y();
    int left = topLeft.x();
    int bottom = bottomLeft.y();

    // �����λ�ö�λ
    int x = left;
    if (maxWidth <= left + width)
    {
        x = (maxWidth - width);
    }

    // �����²���ʾ�������ϲ���ʾ
    int y = bottom;
    if (maxHeight <= bottom + height)
    {
        y = (top < height ? 0 : top - height);
    }

    // �����λ�ö�λ
    pKeyBoard->move(x, y);

    // �����ƶ�����Ҫ�ڼ������̶Ա༭�ؼ��Ƿ�����ڵ����������ڵ�������Ҫ�����ƶ�
    // ����̾���λ��
    QRect rectKb = pKeyBoard->rect();
    QPoint topLeftKb = pKeyBoard->mapToGlobal(rectKb.topLeft());
    QPoint bottomRightKb = pKeyBoard->mapToGlobal(rectKb.bottomRight());

    // �༭�ؼ��������ȫ����ʾ����
    QRect editRectGlobal(topLeft, bottomRight);
    QRect keyboardRectGlobal(topLeftKb, bottomRightKb);

    // �������̺ͱ༭�ؼ��Ƿ�����ص����򣬴��ڣ����������������ʾλ��
    if (keyboardRectGlobal.intersects(editRectGlobal))
    {
        QRect intersectRect = keyboardRectGlobal.intersected(editRectGlobal);
        
        // ��С���ص�������ֱ�Ӻ���
        if (intersectRect.width() <= 5 || intersectRect.height() <= 5)
        {
            return;
        }

        // �Ҳ��޷���ʾ������ʾ�����
        x = left + pEditWidget->width();
        if (maxWidth < x + width)
        {
            x = left > width ?  left - width : 0;
        }

        // �����λ�ö�λ
        pKeyBoard->move(x, y);
    }
}


InputContext::InputContext(QObject* parent)
    : QInputContext(parent), d(new InputContextPrivate())
{
    qApp->installEventFilter(this);

    // �������������
    qApp->setStyle(new ProxyStyle());
}

InputContext::~InputContext()
{
    delete d;
}

// ����״̬
bool InputContext::enabled() const
{
    return d->enabled;
}

void InputContext::setEnabled(bool enabled)
{
    d->enabled = enabled; 
    qDebug() << "InputContext setEnabled" << enabled;
}

// ��Դ·��
QString InputContext::rootPath()
{
    return d->path;
}

void InputContext::setRootPath(const QString& path)
{
    d->path = path;
    qDebug() << "InputContext setRootPath" << path;
}

// ���Դ���
void InputContext::setLanguage(const QString& language)
{
    qDebug() << "InputContext setLanguage" << language;

    // �������Դ���
    d->language = language;

    // ���̳�ʼ��
    d->keyBoardInit();

    // ��Դ��ʼ��
    d->resourceInit();  
}

// ����С�����ַ�
void InputContext::setDecimalPointChar(int chr)
{
    // ɾ��ԭ���ּ���
    KeyBoard* keyBoard = d->getKeyBoard(Qt::Key_F10);
    if (keyBoard)
    {        
        // ��������б���ɾ��
        d->keyBoards.removeOne(keyBoard);

        // �ͷ��ڴ�
        delete keyBoard;
    }

    // ���µ�ǰС�����ַ�
    d->decimalPointChar = chr;

    // �����µ����ּ���
    keyBoard = new DigitKeyBoard(chr);
    if (keyBoard)
    {
        // ��ӵ�������б�
        d->keyBoards.append(keyBoard);
    }
}

// �����û��ʿ�
void InputContext::loadUserPhrase()
{
    // �����û��ʿ�
    if (d->ime)
    {
        d->ime->loadUser(d->path);
    }
}

// ���ߴ�
void InputContext::setMaxSize(const QSize& size)
{
    d->maxSize = size;
}

// ״̬����
void InputContext::reset()
{

}

// ���Դ���
QString InputContext::language()
{
    return d->language;
}

// �Ƿ����
bool InputContext::isComposing() const
{
    return false;
}

// ��ʶ
QString InputContext::identifierName()
{
    return "UNKNOWN";
}

// �¼�����
bool InputContext::filterEvent(const QEvent* event)
{
    int type = event->type();

    if (QEvent::CloseSoftwareInputPanel == type)
    {
        // ��յ�ǰ�����
        d->setKeyBoard(0);
    }
    else if (QEvent::RequestSoftwareInputPanel == type)
    {
        // ���ú����Ч
        if (this->enabled())
        {
            QWidget* widget = this->focusWidget();
            if (widget)
            {
                // ����ؼ���Ӧ�ļ���
                int chr = d->widgetKeyBoard(widget);

                // �л���ָ������
                this->switchToKeyBoard(chr);
            }
        }
    }

    return QInputContext::filterEvent(event);
}

// �����¼�
bool InputContext::eventFilter(QObject *obj, QEvent *event)
{
    int type = event->type();

    if (type == QEvent::KeyPress) 
    {
        qDebug() << "InputContext eventFilter KeyPress";

        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // ƴ�����뷨�������ַ����е�keyֵΪ 0 (��InputContext::onInputButtonClicked(const QString& text)������ʵ��)��
        // �ڴ˴������ų�����ֹƴ�����뷨�����ĵ��ֺ��֣����ٴ���Ϊ���룬�Ӷ����²��ֺ����޷�����
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

// ��������
bool InputContext::onKeyReleaseEvent(int key)
{
    KeyBoard* keyBoard = d->keyBoard;

    // ���ɵ�ǰ���̴����Ƿ���ȡ�������������
    return (keyBoard ? keyBoard->onKeyReleaseEvent(key) : false);
}

// �����
void InputContext::onMouseButtonPressed(const QPoint& globalPos)
{
    KeyBoard* keyBoard = d->keyBoard;

    // �Ƿ��������
    if (keyBoard)
    {
        // �Ƿ���ʾ�����
        if (keyBoard->isVisible())
        {
            // �û���������Ƿ���������ⲿ
            QRect rect = keyBoard->geometry();
            if (!rect.contains(globalPos))
            {
                // ��յ�ǰ�����
                d->setKeyBoard(0);
            }
        }
    }
}

// �л��������
void InputContext::switchToKeyBoard(int chr)
{
    // ��ǰ�����
    KeyBoard* keyBoard = d->keyBoard;
    if (keyBoard)
    {
        // �Ͽ��źŲ�
        this->disconnect(keyBoard, SIGNAL(clicked(int)), this, SLOT(onButtonClicked(int)));
        this->disconnect(keyBoard, SIGNAL(clicked(const QString&)), this, SLOT(onButtonClicked(const QString&)));

        // ��յ�ǰ�����
        d->setKeyBoard(0);
    }

    // �л����������
    keyBoard = d->getKeyBoard(chr);
    if (keyBoard)
    {
        QWidget* widget = this->focusWidget();
        if (0 == widget)
        {
            return;
        }

        // �����������ʾλ��
        d->adjustKeyboardDisplayPosition(keyBoard, widget);

        // �����źŲ�
        this->connect(keyBoard, SIGNAL(clicked(int)), this, SLOT(onButtonClicked(int)), Qt::UniqueConnection);
        this->connect(keyBoard, SIGNAL(clicked(const QString&)), this, SLOT(onButtonClicked(const QString&)), Qt::UniqueConnection);

        // ת��Ϊ��ǰ�����
        d->setKeyBoard(keyBoard);
    }
}

// ���밴��
void InputContext::onButtonClicked(int chr)
{
    if (Qt::Key_Close == chr)
    {
        // �رհ���
        this->onCloseButtonClicked(chr);
    }
    else if (Qt::Key_Enter == chr)
    {
        // �س�����
        // �ͻ�������������sample ID����������̣��������enter�����ʱ����һ��������Ѿ�����ˣ������Ӧ���Զ��رա�
        //           ������Ҫ����ڶ���ҵ��������֮�⣬sample�Ի���֮�ڵ�С��Χ�����ڵ�һ�²��ܹر�����̡�
        this->onCloseButtonClicked(chr);
    }
    else if (Qt::Key_CapsLock == chr)
    {
        // ��д������

    }
    else if (Qt::Key_F1 <= chr && chr <= Qt::Key_F10)
    {
        // ���밴��
        this->onFunctionButtonClicked(chr);
    }
    else
    {
        // ���밴��
        this->onInputButtonClicked(chr);
    }
}

void InputContext::onButtonClicked(const QString& text)
{
    this->onInputButtonClicked(text);
}

// �رհ���
void InputContext::onCloseButtonClicked(int chr)
{
    KeyBoard* keyBoard = d->keyBoard;
    if (keyBoard)
    {
        // ��յ�ǰ�����
        d->setKeyBoard(0);
    }
}

// ���밴��
void InputContext::onInputButtonClicked(int chr)
{
    // ����ؼ�
    QWidget* widget = this->focusWidget();
    if (widget)
    {
        // �ı�
        QString text = QChar(chr);
        if (d->keyBoard->capslock())
        {
            text = text.toUpper();
        }
        else
        {
            text = text.toLower();
        }

        // ��������
        QKeyEvent keyPress(QEvent::KeyPress, chr, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyPress);

        // �����ͷ�
        QKeyEvent keyRelease(QEvent::KeyRelease, chr, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyRelease);
    }
}

void InputContext::onInputButtonClicked(const QString& text)
{
    // ����ؼ�
    QWidget* widget = this->focusWidget();
    if (widget)
    {
        // ��������
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyPress);

        // �����ͷ�
        QKeyEvent keyRelease(QEvent::KeyRelease, 0, Qt::NoModifier, text);
        QApplication::sendEvent(widget, &keyRelease);
    }
}

// ���ܰ���
void InputContext::onFunctionButtonClicked(int chr)
{
    // �л���Ŀ�����
    this->switchToKeyBoard(chr);
}