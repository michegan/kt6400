#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>

#include "imebar.h"
#include "keybutton.h"


// ������ʾ�ָ���
#define PHRASE_SEPERATOR   "'"

// �߾�
static int s_xmargin = 10;
static int s_ymargin = 6;

// �������߶�
static int s_topbar_height = 30;
static int s_bottombar_height = 35;

// ��ѡ����ָ���
static QString s_separator = QString(Qt::Key_Tab);


class ImeBarPrivate
{
public:
    ImeBarPrivate();
    ~ImeBarPrivate();

    // �Զ�ʹ�ܷ�ҳ��ť
    void autoEnablePageButtons();

    // ������ǰҳ��ѡ����
    void makeCurrentPageCandidatePhrases();

    // ����ȫ����ѡ���飨���ָ�����
    void makeCandidatePhrases(const QFontMetrics& fontMetrics, const QStringList& candidatePhrases, int maxWidth);

    // ������ѡƴ��
    void makeSelectedPhraseForDisplay(const QStringList& selectPhrases);

public:
    // ��ť
    KeyButton* btnPageUp;
    KeyButton* btnPageDown;

    // �������
    QString focusPhase;

    // ��ѡ����
    QStringList selectPhrases;

    // ����ʾ��ѡ����
    QString displaySelectPhrase;

    // ��ǰ��ѡҳ
    int currentPage;
    // ȫ����ѡ���飨���ָ�����
    QStringList candidatePhrases;
    // ��ǰҳ��ѡ����
    QStringList currentPageCandidatePhrases;
};

ImeBarPrivate::ImeBarPrivate()
    : btnPageUp(new KeyButton(0)), btnPageDown(new KeyButton(0)), focusPhase(""), currentPage(0)
{

}

ImeBarPrivate::~ImeBarPrivate()
{

}

// �Զ�ʹ�ܷ�ҳ��ť
void ImeBarPrivate::autoEnablePageButtons()
{
    int maxPages = this->candidatePhrases.count(s_separator);

    // ��ҳ��ťʹ��
    this->btnPageUp->setEnabled(0 < this->currentPage);
    this->btnPageDown->setEnabled(this->currentPage < maxPages);
}

// ������ǰҳ��ѡ����
void ImeBarPrivate::makeCurrentPageCandidatePhrases()
{
    // ���
    this->currentPageCandidatePhrases.clear();

    // ���´�����ǰҳ��ѡ����
    for (int i = 0, page = 0; i < this->candidatePhrases.size(); i++)
    {
        QString candidatePhase = this->candidatePhrases.at(i);

        if (s_separator == candidatePhase)
        {
            // �ָ�����ҳ������
            page ++;
        }
        else
        {
            // ������ǰҳ��ѡ����
            if (this->currentPage <= page && page < this->currentPage + 1)
            {
                this->currentPageCandidatePhrases.append(candidatePhase);
            }
        }
    }
}

// ����ȫ����ѡ���飨���ָ�����
void ImeBarPrivate::makeCandidatePhrases(const QFontMetrics& fontMetrics, const QStringList& candidatePhrases, int maxWidth)
{
    int x = 0;
    int margin = s_xmargin * 2;

    // �Ż���һ������ʱ��ѡ����ʾ�������⣬�����ֿ��ļ�δȫ��������������ص��ڴ��У����Դ˴�������ʱ���������ȡ�����µ�һ������ʱ��ʾ��ѡ�ʽ���
    // ����Ŀǰʹ�õ��ǵȿ����壬����ֻ����һ�����ֵĿ�ȣ��Լ������Ŀ�ȣ����ڼ������ʾ���ֿ�ȣ������ٶȼ�������ʮ������
    // ���ֿ��
    int singleWordWidth = fontMetrics.width(QString(QChar(0x6db4)));
    // ��ſ��
    int indexWidth = fontMetrics.width("6.");

    // ��պ�ѡҳ�б�
    this->candidatePhrases.clear();

    // ���´�����ѡҳ�б�
    int iIndex = 0;
    for (int i = 0, j = 0; i < candidatePhrases.size();)
    {
        iIndex++;
        QString candidatePhase = QString("%1.%2").arg(iIndex).arg(candidatePhrases.at(i));

        int width = indexWidth + singleWordWidth * candidatePhrases.at(i).count();
        if (x + width + margin < maxWidth)
        {
            i++;
            x += (width + margin);

            // �������
            this->candidatePhrases.append(candidatePhase);
        }
        else
        {
            x = 0;
            iIndex = 0;

            // ����ָ���
            j ++;
            this->candidatePhrases.append(s_separator);
        }
    }
}

// ������ѡƴ��
void ImeBarPrivate::makeSelectedPhraseForDisplay(const QStringList& selectPhrases)
{
    // �Էָ����ķ�ʽ����ƴ��
    QString strSeperator = "";
    QString strPinyinAndPhrase = "";
    foreach (QString phrase, selectPhrases)
    {
        if (!phrase.isEmpty())
        {
            // ��ʱ����ʾ���ַ�����ֻ������ĸ������
            // ƴ��֮����Ҫ��ʾ�ָ���
            if (phrase.at(0).isUpper() || phrase.at(0).isLower())
            {
                strSeperator = PHRASE_SEPERATOR;
            }
            // �û���ѡ�к���֮�䲻��Ҫ�ָ���
            else
            {
                strSeperator = "";
                strPinyinAndPhrase = strPinyinAndPhrase.remove(PHRASE_SEPERATOR);
            }
        }

        strPinyinAndPhrase += phrase + strSeperator;
    }

    // ���һλΪ�ָ�������ȥ��
    strPinyinAndPhrase = strPinyinAndPhrase.trimmed();
    if (strPinyinAndPhrase.endsWith(PHRASE_SEPERATOR))
    {
        strPinyinAndPhrase = strPinyinAndPhrase.left(strPinyinAndPhrase.count() - 1);
    }

    // ���մ���ʾ�ַ���
    displaySelectPhrase = strPinyinAndPhrase;
}


ImeBar::ImeBar()
    : QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint), d(new ImeBarPrivate())
{
    // Ĭ������
    QFont font = this->font();

    font.setBold(true);
    font.setPixelSize(16);

    this->setFont(font);

    // ����ý���
    this->setFocusPolicy(Qt::NoFocus);

    // ����ɫ
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xc5, 0xc8, 0xce));
    this->setPalette(palette);

    // ��ť
    d->btnPageUp->setParent(this);
    d->btnPageUp->setImage("pageup");

    d->btnPageDown->setParent(this);
    d->btnPageDown->setImage("pagedown");

    // ���沼��
    d->btnPageUp->setGeometry(494, s_topbar_height + s_ymargin, 38, s_bottombar_height);
    d->btnPageDown->setGeometry(534, s_topbar_height + s_ymargin, 38, s_bottombar_height);

    // �����źŲ�
    this->connect(d->btnPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(d->btnPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
}

ImeBar::~ImeBar()
{
    delete d;
}

// �������
void ImeBar::clear()
{
    // ��ť
    d->btnPageUp->setEnabled(false);
    d->btnPageDown->setEnabled(false);

    // �������
    d->focusPhase.clear();

    // ��ѡ����
    d->selectPhrases.clear();
    // ������ʾ����ѡ����
    d->displaySelectPhrase = "";

    // ��ǰ��ѡҳ
    d->currentPage = 0;
    // ȫ����ѡ���飨���ָ�����
    d->candidatePhrases.clear();
    // ��ǰҳ��ѡ����
    d->currentPageCandidatePhrases.clear();
}

// �ⲿѡ��
bool ImeBar::selectFirst()
{
    bool accepted = !d->currentPageCandidatePhrases.isEmpty();
    if (accepted)
    {
        // ��ǰҳ��ѡ�ʵ��׸�����
        QString phrase = d->currentPageCandidatePhrases.first();
        emit phraseSelected(phrase.mid(2));
    }
    return accepted;
}

// ��������
bool ImeBar::processInput(int key)
{
    bool bAccepted = false;
    QChar qCh = QChar(key);
    if (Qt::Key_Enter == key || Qt::Key_Space == key || Qt::Key_Return == key)
    {
        bAccepted = selectFirst();
    }
    else if (qCh.isNumber())
    {
        bAccepted = selectPhraseByNumber(key);
    }
    else if (qCh == '=' || qCh == '.')
    {
        bAccepted = turnPageDown();
    }
    else if (qCh == '-' || qCh == ',')
    {
        bAccepted = turnPageUp();
    }

    return bAccepted;
}

// ����ѡ��
bool ImeBar::selectPhraseByNumber(int key)
{
    // �޺�ѡ����ʱ��ֱ�ӽ��пؼ�����
    if (d->currentPageCandidatePhrases.count() == 0)
    {
        return false;
    }

    int iIndex = QString(QChar(key)).toInt() - 1;
    if (iIndex >=0 && iIndex < d->currentPageCandidatePhrases.count())
    {
        QString phrase = d->currentPageCandidatePhrases.at(iIndex);
        emit phraseSelected(phrase.mid(2));
    }

    return true;
}

// ��ѡ����ǰ��ҳ
bool ImeBar::turnPageUp()
{
    // �޺�ѡ����ʱ��ֱ�ӽ��пؼ�����
    if (d->currentPageCandidatePhrases.count() == 0)
    {
        return false;
    }

    onBtnPageUpClicked();
    return true;
}

// ��ѡ�����ҳ
bool ImeBar::turnPageDown()
{
    // �޺�ѡ����ʱ��ֱ�ӽ��пؼ�����
    if (d->currentPageCandidatePhrases.count() == 0)
    {
        return false;
    }

    onBtnPageDownClicked();
    return true;
}

// ����仯
void ImeBar::onPhrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases)
{
    // ���õ�ǰҳ
    d->currentPage = 0;

    // ���´���
    d->selectPhrases = selectPhrases;

    // ����ȫ����ѡ���飨���ָ�����
    d->makeCandidatePhrases(this->fontMetrics(), candidatePhrases, 365);

    // ������ǰҳ��ѡ����
    d->makeCurrentPageCandidatePhrases();

    // �Զ�ʹ�ܷ�ҳ��ť
    d->autoEnablePageButtons();

    // ������ѡ����ʹ�ѡƴ����ʾ
    d->makeSelectedPhraseForDisplay(selectPhrases);
    QFontMetrics fontMetrics = this->fontMetrics();
    int widthString = (s_xmargin + fontMetrics.width(d->displaySelectPhrase) + s_xmargin);
    if (widthString > (rect().width() * 2 / 3))
    {
        // ƴ����ʾ������
        emit pinyinDisplayRegionFull();
    }

    // ˢ�½���
    this->update();
}

// �����¼�
void ImeBar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QFontMetrics fontMetrics = this->fontMetrics();

    // ��ѡ���鱳��
    painter.fillRect(s_xmargin, s_ymargin, 562, s_topbar_height, QColor(0xed, 0xef, 0xf3));

    // ��ѡ����
    int x1 = s_xmargin * 2;
    int y1 = s_ymargin;
    
    // �������ؿ��
    int width1 = fontMetrics.width(d->displaySelectPhrase);
    int width2 = (s_xmargin + width1 + s_xmargin);

    // ������ʾλ��
    QRect rect(x1, y1, width2, s_topbar_height);

    // ���л����ı�
    painter.drawText(rect, Qt::AlignCenter, d->displaySelectPhrase);

    // ��ǰҳ��ѡ���鱳��
    painter.fillRect(s_xmargin, s_ymargin + s_topbar_height, 562, s_bottombar_height, QColor(0x8d, 0x92, 0xa0));

    // ��ǰҳ��ѡ����
    int x2 = s_xmargin * 2;
    int y2 = s_ymargin + s_topbar_height;
    
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // �������ؿ��
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // ������ʾλ��
        QRect rect(x2, y2, width2, s_bottombar_height);

        // �������
        QColor color = (d->focusPhase == phrase ? QColor(0x42, 0x44, 0x4a) : QColor(0x8d, 0x92, 0xa0));
        painter.fillRect(rect, color);

        // ���л����ı�
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, phrase);

        // X��ƫ��
        x2 += width2;
    }
}

// ����¼�
void ImeBar::mousePressEvent(QMouseEvent* event)
{
    int x2 = s_xmargin * 2;
    int y2 = s_ymargin * 2 + s_topbar_height;

    QFontMetrics fontMetrics = this->fontMetrics();
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // �������ؿ��
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // ������ʾλ��
        QRect rect(x2, y2, width2, s_bottombar_height - 2 * s_ymargin);
        if (rect.contains(event->pos()))
        {
            // ��¼�������
            d->focusPhase  = phrase;
            break;
        }

        // X��ƫ��
        x2 += width2;
    }

    // ˢ�½���
    this->update();
}

void ImeBar::mouseReleaseEvent(QMouseEvent* event)
{
    // ��ս������
    d->focusPhase  = "";

    int x2 = s_xmargin * 2;
    int y2 = s_ymargin * 2 + s_topbar_height;

    QFontMetrics fontMetrics = this->fontMetrics();
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // �������ؿ��
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // ������ʾλ��
        QRect rect(x2, y2, width2, s_bottombar_height - 2 * s_ymargin);
        if (rect.contains(event->pos()))
        {
            emit phraseSelected(phrase.mid(2));
            break;
        }

        // X��ƫ��
        x2 += width2;
    }

    // ˢ�½���
    this->update();
}

// ��ť���
void ImeBar::onBtnPageUpClicked()
{
    if (d->currentPage <= 0)
    {
        return;
    }

    // ���µ�ǰҳ
    d->currentPage --;

    // ������ǰҳ��ѡ����
    d->makeCurrentPageCandidatePhrases();

    // �Զ�ʹ�ܷ�ҳ��ť
    d->autoEnablePageButtons();

    // ˢ����ʾ
    this->update();
}

void ImeBar::onBtnPageDownClicked()
{
    int maxPages = d->candidatePhrases.count(s_separator);
    if (d->currentPage >= maxPages)
    {
        return;
    }

    // ���µ�ǰҳ
    d->currentPage ++;

    // ������ǰҳ��ѡ����
    d->makeCurrentPageCandidatePhrases();

    // �Զ�ʹ�ܷ�ҳ��ť
    d->autoEnablePageButtons();

    // ˢ����ʾ
    this->update();
}