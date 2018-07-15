#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>

#include "imebar.h"
#include "keybutton.h"


// 词组显示分隔符
#define PHRASE_SEPERATOR   "'"

// 边距
static int s_xmargin = 10;
static int s_ymargin = 6;

// 输入条高度
static int s_topbar_height = 30;
static int s_bottombar_height = 35;

// 候选词组分隔符
static QString s_separator = QString(Qt::Key_Tab);


class ImeBarPrivate
{
public:
    ImeBarPrivate();
    ~ImeBarPrivate();

    // 自动使能翻页按钮
    void autoEnablePageButtons();

    // 创建当前页候选词组
    void makeCurrentPageCandidatePhrases();

    // 创建全部候选词组（带分隔符）
    void makeCandidatePhrases(const QFontMetrics& fontMetrics, const QStringList& candidatePhrases, int maxWidth);

    // 创建待选拼音
    void makeSelectedPhraseForDisplay(const QStringList& selectPhrases);

public:
    // 按钮
    KeyButton* btnPageUp;
    KeyButton* btnPageDown;

    // 焦点词组
    QString focusPhase;

    // 已选词组
    QStringList selectPhrases;

    // 待显示已选词组
    QString displaySelectPhrase;

    // 当前候选页
    int currentPage;
    // 全部候选词组（带分隔符）
    QStringList candidatePhrases;
    // 当前页候选词组
    QStringList currentPageCandidatePhrases;
};

ImeBarPrivate::ImeBarPrivate()
    : btnPageUp(new KeyButton(0)), btnPageDown(new KeyButton(0)), focusPhase(""), currentPage(0)
{

}

ImeBarPrivate::~ImeBarPrivate()
{

}

// 自动使能翻页按钮
void ImeBarPrivate::autoEnablePageButtons()
{
    int maxPages = this->candidatePhrases.count(s_separator);

    // 翻页按钮使能
    this->btnPageUp->setEnabled(0 < this->currentPage);
    this->btnPageDown->setEnabled(this->currentPage < maxPages);
}

// 创建当前页候选词组
void ImeBarPrivate::makeCurrentPageCandidatePhrases()
{
    // 清空
    this->currentPageCandidatePhrases.clear();

    // 重新创建当前页候选词组
    for (int i = 0, page = 0; i < this->candidatePhrases.size(); i++)
    {
        QString candidatePhase = this->candidatePhrases.at(i);

        if (s_separator == candidatePhase)
        {
            // 分隔符，页数递增
            page ++;
        }
        else
        {
            // 创建当前页候选词组
            if (this->currentPage <= page && page < this->currentPage + 1)
            {
                this->currentPageCandidatePhrases.append(candidatePhase);
            }
        }
    }
}

// 创建全部候选词组（带分隔符）
void ImeBarPrivate::makeCandidatePhrases(const QFontMetrics& fontMetrics, const QStringList& candidatePhrases, int maxWidth)
{
    int x = 0;
    int margin = s_xmargin * 2;

    // 优化第一次输入时候选词显示过慢问题，由于字库文件未全部将所有字体加载到内存中，所以此处计算宽度时，才逐个获取，导致第一次输入时显示候选词较慢
    // 由于目前使用的是等宽字体，所以只计算一个汉字的宽度，以及索引的宽度，用于计算待显示文字宽度，计算速度即可提升十倍左右
    // 单字宽度
    int singleWordWidth = fontMetrics.width(QString(QChar(0x6db4)));
    // 序号宽度
    int indexWidth = fontMetrics.width("6.");

    // 清空候选页列表
    this->candidatePhrases.clear();

    // 重新创建候选页列表
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

            // 插入词组
            this->candidatePhrases.append(candidatePhase);
        }
        else
        {
            x = 0;
            iIndex = 0;

            // 插入分隔符
            j ++;
            this->candidatePhrases.append(s_separator);
        }
    }
}

// 创建待选拼音
void ImeBarPrivate::makeSelectedPhraseForDisplay(const QStringList& selectPhrases)
{
    // 以分隔符的方式隔断拼音
    QString strSeperator = "";
    QString strPinyinAndPhrase = "";
    foreach (QString phrase, selectPhrases)
    {
        if (!phrase.isEmpty())
        {
            // 此时待显示的字符串中只包含字母和中文
            // 拼音之间需要显示分隔符
            if (phrase.at(0).isUpper() || phrase.at(0).isLower())
            {
                strSeperator = PHRASE_SEPERATOR;
            }
            // 用户已选中汉字之间不需要分隔符
            else
            {
                strSeperator = "";
                strPinyinAndPhrase = strPinyinAndPhrase.remove(PHRASE_SEPERATOR);
            }
        }

        strPinyinAndPhrase += phrase + strSeperator;
    }

    // 最后一位为分隔符，则去除
    strPinyinAndPhrase = strPinyinAndPhrase.trimmed();
    if (strPinyinAndPhrase.endsWith(PHRASE_SEPERATOR))
    {
        strPinyinAndPhrase = strPinyinAndPhrase.left(strPinyinAndPhrase.count() - 1);
    }

    // 最终待显示字符串
    displaySelectPhrase = strPinyinAndPhrase;
}


ImeBar::ImeBar()
    : QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint), d(new ImeBarPrivate())
{
    // 默认字体
    QFont font = this->font();

    font.setBold(true);
    font.setPixelSize(16);

    this->setFont(font);

    // 不获得焦点
    this->setFocusPolicy(Qt::NoFocus);

    // 背景色
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xc5, 0xc8, 0xce));
    this->setPalette(palette);

    // 按钮
    d->btnPageUp->setParent(this);
    d->btnPageUp->setImage("pageup");

    d->btnPageDown->setParent(this);
    d->btnPageDown->setImage("pagedown");

    // 界面布局
    d->btnPageUp->setGeometry(494, s_topbar_height + s_ymargin, 38, s_bottombar_height);
    d->btnPageDown->setGeometry(534, s_topbar_height + s_ymargin, 38, s_bottombar_height);

    // 关联信号槽
    this->connect(d->btnPageUp, SIGNAL(clicked()), this, SLOT(onBtnPageUpClicked()));
    this->connect(d->btnPageDown, SIGNAL(clicked()), this, SLOT(onBtnPageDownClicked()));
}

ImeBar::~ImeBar()
{
    delete d;
}

// 清除输入
void ImeBar::clear()
{
    // 按钮
    d->btnPageUp->setEnabled(false);
    d->btnPageDown->setEnabled(false);

    // 焦点词组
    d->focusPhase.clear();

    // 已选词组
    d->selectPhrases.clear();
    // 用于显示的已选词组
    d->displaySelectPhrase = "";

    // 当前候选页
    d->currentPage = 0;
    // 全部候选词组（带分隔符）
    d->candidatePhrases.clear();
    // 当前页候选词组
    d->currentPageCandidatePhrases.clear();
}

// 外部选词
bool ImeBar::selectFirst()
{
    bool accepted = !d->currentPageCandidatePhrases.isEmpty();
    if (accepted)
    {
        // 当前页候选词的首个单词
        QString phrase = d->currentPageCandidatePhrases.first();
        emit phraseSelected(phrase.mid(2));
    }
    return accepted;
}

// 处理输入
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

// 数字选词
bool ImeBar::selectPhraseByNumber(int key)
{
    // 无候选词组时，直接交有控件处理
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

// 候选词向前翻页
bool ImeBar::turnPageUp()
{
    // 无候选词组时，直接交有控件处理
    if (d->currentPageCandidatePhrases.count() == 0)
    {
        return false;
    }

    onBtnPageUpClicked();
    return true;
}

// 候选词向后翻页
bool ImeBar::turnPageDown()
{
    // 无候选词组时，直接交有控件处理
    if (d->currentPageCandidatePhrases.count() == 0)
    {
        return false;
    }

    onBtnPageDownClicked();
    return true;
}

// 词组变化
void ImeBar::onPhrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases)
{
    // 重置当前页
    d->currentPage = 0;

    // 更新词组
    d->selectPhrases = selectPhrases;

    // 创建全部候选词组（带分隔符）
    d->makeCandidatePhrases(this->fontMetrics(), candidatePhrases, 365);

    // 创建当前页候选词组
    d->makeCurrentPageCandidatePhrases();

    // 自动使能翻页按钮
    d->autoEnablePageButtons();

    // 制作已选词组和待选拼音显示
    d->makeSelectedPhraseForDisplay(selectPhrases);
    QFontMetrics fontMetrics = this->fontMetrics();
    int widthString = (s_xmargin + fontMetrics.width(d->displaySelectPhrase) + s_xmargin);
    if (widthString > (rect().width() * 2 / 3))
    {
        // 拼音显示区域满
        emit pinyinDisplayRegionFull();
    }

    // 刷新界面
    this->update();
}

// 绘制事件
void ImeBar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QFontMetrics fontMetrics = this->fontMetrics();

    // 已选词组背景
    painter.fillRect(s_xmargin, s_ymargin, 562, s_topbar_height, QColor(0xed, 0xef, 0xf3));

    // 已选词组
    int x1 = s_xmargin * 2;
    int y1 = s_ymargin;
    
    // 词组像素宽度
    int width1 = fontMetrics.width(d->displaySelectPhrase);
    int width2 = (s_xmargin + width1 + s_xmargin);

    // 词组显示位置
    QRect rect(x1, y1, width2, s_topbar_height);

    // 居中绘制文本
    painter.drawText(rect, Qt::AlignCenter, d->displaySelectPhrase);

    // 当前页候选词组背景
    painter.fillRect(s_xmargin, s_ymargin + s_topbar_height, 562, s_bottombar_height, QColor(0x8d, 0x92, 0xa0));

    // 当前页候选词组
    int x2 = s_xmargin * 2;
    int y2 = s_ymargin + s_topbar_height;
    
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // 词组像素宽度
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // 词组显示位置
        QRect rect(x2, y2, width2, s_bottombar_height);

        // 焦点词组
        QColor color = (d->focusPhase == phrase ? QColor(0x42, 0x44, 0x4a) : QColor(0x8d, 0x92, 0xa0));
        painter.fillRect(rect, color);

        // 居中绘制文本
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, phrase);

        // X向偏移
        x2 += width2;
    }
}

// 鼠标事件
void ImeBar::mousePressEvent(QMouseEvent* event)
{
    int x2 = s_xmargin * 2;
    int y2 = s_ymargin * 2 + s_topbar_height;

    QFontMetrics fontMetrics = this->fontMetrics();
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // 词组像素宽度
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // 词组显示位置
        QRect rect(x2, y2, width2, s_bottombar_height - 2 * s_ymargin);
        if (rect.contains(event->pos()))
        {
            // 记录焦点词组
            d->focusPhase  = phrase;
            break;
        }

        // X向偏移
        x2 += width2;
    }

    // 刷新界面
    this->update();
}

void ImeBar::mouseReleaseEvent(QMouseEvent* event)
{
    // 清空焦点词组
    d->focusPhase  = "";

    int x2 = s_xmargin * 2;
    int y2 = s_ymargin * 2 + s_topbar_height;

    QFontMetrics fontMetrics = this->fontMetrics();
    foreach (QString phrase, d->currentPageCandidatePhrases)
    {
        // 词组像素宽度
        int width1 = fontMetrics.width(phrase);
        int width2 = (s_xmargin + width1 + s_xmargin);

        // 词组显示位置
        QRect rect(x2, y2, width2, s_bottombar_height - 2 * s_ymargin);
        if (rect.contains(event->pos()))
        {
            emit phraseSelected(phrase.mid(2));
            break;
        }

        // X向偏移
        x2 += width2;
    }

    // 刷新界面
    this->update();
}

// 按钮点击
void ImeBar::onBtnPageUpClicked()
{
    if (d->currentPage <= 0)
    {
        return;
    }

    // 更新当前页
    d->currentPage --;

    // 创建当前页候选词组
    d->makeCurrentPageCandidatePhrases();

    // 自动使能翻页按钮
    d->autoEnablePageButtons();

    // 刷新显示
    this->update();
}

void ImeBar::onBtnPageDownClicked()
{
    int maxPages = d->candidatePhrases.count(s_separator);
    if (d->currentPage >= maxPages)
    {
        return;
    }

    // 更新当前页
    d->currentPage ++;

    // 创建当前页候选词组
    d->makeCurrentPageCandidatePhrases();

    // 自动使能翻页按钮
    d->autoEnablePageButtons();

    // 刷新显示
    this->update();
}