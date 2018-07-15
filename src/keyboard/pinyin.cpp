#include <QHash>
#include <QFile>
#include <QtDebug>
#include <QTextStream>

#include "pinyin.h"


// 最大候选词数
#define MAX_CANDIDATES  (200)


class PinYinPrivate
{
public:
    PinYinPrivate();
    ~PinYinPrivate();

    // 是否输入
    bool isPrint(int chr);

    // 是否单词
    bool isWord(const QString& text);

    // 截断
    QString trim(const QString& text);

    // 加载
    QStringList load(const QString& filename);

    // 候选词组
    QStringList getCandidatePhrases(const QStringList& words);

    // 根据分隔符截断字符串，与split函数功能相同，此处重写以提高效率
    QStringList localSplit(const QString& strSrc, const QString& strSep, int iSize);

    // 字符串中是否只包含了大写字母
    bool isUpperString(QString strSrc);

public:
    // 已选词组
    QStringList selectPhrases;
    // 未选单词
    QStringList unselectWords;
    // 已选拼音
    QStringList seletectedPinyin;

public:
    // 词组（正向，拼音->汉字）
    QHash<QString, QStringList> userPhrases;
    QHash<QString, QStringList> systemPhrases;
    // 单词（正向，拼音->汉字）
    QHash<QString, QStringList> userWords;
    QHash<QString, QStringList> systemWords;
    // 词组（反向，汉字->拼音）
    // 多音字，存在多个拼音
    QHash<QString, QStringList> userPinyins;
    QHash<QString, QStringList> systemPinyins;

    // 用户主动分词
    bool bSeperatePhraseByUser;

    // 拼音显示区域满
    bool bPinyinDisplayRegionFull;
};

PinYinPrivate::PinYinPrivate()
{
    bSeperatePhraseByUser = false;
    bPinyinDisplayRegionFull = false;
}

PinYinPrivate::~PinYinPrivate()
{

}

// 是否可打印
bool PinYinPrivate::isPrint(int chr)
{
    return (0x20 < chr && chr < 0x7F);
}

// 是否单词
bool PinYinPrivate::isWord(const QString& text)
{
    bool ret = false;

    // 系统词库
    QStringList words = this->systemWords.keys();
    // 用户词库
    words.append(this->userWords.keys());

    foreach (QString word, words)
    {
        if (word.startsWith(text))
        {
            ret = true;
            break;
        }
    }

    return ret;
}

// 截断
QString PinYinPrivate::trim(const QString& text)
{
    if (text.isEmpty())
    {
        return text;
    }
    else
    {
        int size = text.length();
        return text.left(size - 1);
    }
}

// 根据分隔符截断字符串，与split函数功能相同，此处重写以提高效率
QStringList PinYinPrivate::localSplit(const QString& strSrc, const QString& strSep, int iSize)
{
    QStringList dstList;
    dstList.reserve(iSize);
    int iIndexStart = 0;
    int iIndexEnd = strSrc.indexOf(strSep, 0);

    while (iIndexEnd >= 0)
    {
        dstList.append(strSrc.mid(iIndexStart, iIndexEnd - iIndexStart));

        iIndexStart = iIndexEnd + 1;
        iIndexEnd = strSrc.indexOf(strSep, iIndexStart);
    }

    dstList.append(strSrc.mid((iIndexStart)));
    return dstList;
}

// 字符串中是否只包含了大写字母
bool PinYinPrivate::isUpperString(QString strSrc)
{
    if (strSrc.isEmpty())
    {
        return false;
    }

    QChar qChr = 0;
    int iCount = strSrc.count();
    for (int i=0; i<iCount; i++)
    {
        qChr = strSrc.at(i);
        if (!qChr.isUpper())
        {
            return false;
        }
    }

    return true;
}

// 加载
QStringList PinYinPrivate::load(const QString& filename)
{
    QStringList lines;
    QFile file(filename);

    qDebug() << "PinYin load" << filename;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // 一次性加载文本内容，减少大循环所带来的资源消耗
        QTextStream stream(&file);
        QString line = stream.readAll();

        // 自定义拆分
        lines = this->localSplit(line, "\n", 170000);

        file.close();
    }
    else
    {
        qWarning() << "PinYinPrivate load open fail";
    }

    return lines;
}

// 候选词组
QStringList PinYinPrivate::getCandidatePhrases(const QStringList& words)
{
    QStringList phrases;

    // 词组（全匹配）
    {
        for (int length = words.length(); length > 0; length--)
        {
            QStringList list = words.mid(0, length);
            // 词组才需要在词组哈希表中查找对应的词组
            if (list.count() >= 2)
            {
                QString key = list.join("'");

                // 用户词库
                if (!(this->userPhrases.value(key, QStringList()).isEmpty()))
                {
                    phrases.append(this->userPhrases.value(key));
                }
                // 系统词库
                if (!(this->systemPhrases.value(key, QStringList()).isEmpty()))
                {
                    phrases.append(this->systemPhrases.value(key));
                }
            }
        }
    }

    // 单词（全匹配）
    {
        QString word = words.first();

        // 用户词库
        if (!(this->userWords.value(word, QStringList()).isEmpty()))
        {
            phrases.append(this->userWords.value(word));
        }
        // 系统词库
        if (!(this->systemWords.value(word, QStringList()).isEmpty()))
        {
            phrases.append(this->systemWords.value(word));
        }
    }

    // 如果前面都没有匹配到，则模糊匹配
    if (phrases.isEmpty())
    {
        QString word = words.first();

        // 用户词库
        QStringList keys = this->userWords.keys();
        foreach (QString key, keys)
        {
            if (key.startsWith(word))
            {
                phrases.append(this->userWords.value(key));
                break;
            }
        }

        // 系统词库
        keys = this->systemWords.keys();
        foreach (QString key, keys)
        {
            if (key.startsWith(word))
            {
                phrases.append(this->systemWords.value(key));
                break;
            }
        }
    }

    // 单独的i、u、v无法找到与其对应的候选汉字或词组，
    // 此时直接将该字母做为候选词
    QString strUnselectedWord = words.first().trimmed();
    if (phrases.isEmpty() && (strUnselectedWord.compare("u") == 0 
        || strUnselectedWord.compare("i") == 0 || strUnselectedWord.compare("v") == 0))
    {
        phrases.append(strUnselectedWord);
    }

    // 处理大写字母字符串,直接作为候选词
    if (phrases.isEmpty() && isUpperString(strUnselectedWord))
    {
        phrases.append(strUnselectedWord);
    }

    return phrases;
}


PinYin::PinYin()
    : QObject(), d(new PinYinPrivate())
{

}

PinYin::~PinYin()
{
    delete d;
}

// 清除输入
void PinYin::clear()
{
    // 清空已选词组
    d->selectPhrases.clear();
    // 清空待选单词
    d->unselectWords.clear();
    // 清空已选拼音
    d->seletectedPinyin.clear();

    // 拼音显示区域满
    d->bPinyinDisplayRegionFull = false;
    d->bSeperatePhraseByUser = false;
}

// 新字符
bool PinYin::onNewChar(int chr)
{
    bool ret = true;

    if (Qt::Key_Enter == chr || Qt::Key_Return == chr)
    {
        // 选词
        if (d->unselectWords.isEmpty() && d->selectPhrases.isEmpty())
        {
            // 无输入可选词，交由上层处理
            ret = false;
        }
        else
        {
            // 全部待选单词转换为已选词组
            d->selectPhrases.append(d->unselectWords);

            // 清空待选单词
            d->unselectWords.clear();
        }
    }
    else if (Qt::Key_Backspace == chr)
    {
        d->bPinyinDisplayRegionFull = false;

        // 删除当前录入
        if (d->unselectWords.isEmpty())
        {
            // 无单词可删除，交由上层处理
            ret = false;
        }
        else if (d->bSeperatePhraseByUser)
        {
            d->bSeperatePhraseByUser = false;
        }
        else
        {
            // 无选中词组时
            if (d->seletectedPinyin.isEmpty())
            {
                // 最后一个单词
                QString last = d->unselectWords.last();

                // 截断
                last = d->trim(last);

                // 删除最后一个单词
                d->unselectWords.pop_back();

                // 重新追加新单词
                if (!last.isEmpty())
                {
                    d->unselectWords.append(last);
                }
            }
            else
            {
                // 去掉最后一个已选词组
                QString strLastPhrase =  d->selectPhrases.last();
                d->selectPhrases.removeLast();

                // 用户选择为词组时，需要将词组对应的拼音全部插入待选拼音中
                for (int i=0; i<strLastPhrase.count(); i++)
                {
                    // 将第一个已选拼音插入待选拼音链表
                    d->unselectWords.push_front(d->seletectedPinyin.last());
                    // 去掉第一个已选拼音
                    d->seletectedPinyin.removeLast();
                }
            }
        }
    }
    else if (Qt::Key_Clear == chr)
    {
        // 清空当前录入
        // 清空已选词组
        d->selectPhrases.clear();
        // 清空待选单词
        d->unselectWords.clear();
        // 清空已选拼音
        d->seletectedPinyin.clear();

        d->bPinyinDisplayRegionFull = false;
        d->bSeperatePhraseByUser = false;
    }
    else if (QChar(chr) == QChar('\'') && !d->unselectWords.isEmpty())
    {
        // 处理拼音分隔符
        d->bSeperatePhraseByUser = true;
        ret = true;
    }
    else if (QChar(chr).isNumber() || QChar(chr).isSymbol() || QChar(chr).isPunct())
    {
        // 不处理数字，标点符号
        ret = false;
    }
    else if (d->unselectWords.isEmpty() && d->selectPhrases.isEmpty() && QChar(chr).isUpper())
    {
        // 直接输入大写字母，则交由上层处理
        return false;
    }
    else
    {
        if (d->isPrint(chr))
        {
            if (d->bPinyinDisplayRegionFull)
            {
                ret = true;
            }
            else
            {
                // 处理用户输入的大写字母
                if (QChar(chr).isUpper())
                {
                    if (d->unselectWords.isEmpty())
                    {
                        d->unselectWords.append(QString(chr));
                    }
                    else
                    {
                        QString word = d->unselectWords.last();
                        if (!word.isEmpty())
                        {
                            if (word.at(0).isUpper())
                            {
                                // 删除原最后一个单词
                                d->unselectWords.pop_back();

                                // 追加新单词
                                d->unselectWords.append(word + QString(chr));
                            }
                            else
                            {
                                d->unselectWords.append(QString(chr));
                            }
                        }
                        else
                        {
                            qDebug() << "PinYin onNewChar, lastest unselect words is empty";
                        }
                    }
                }
                else
                {
                    QString tchr = QString(QChar(chr));
                    if (d->unselectWords.isEmpty())
                    {
                        // 新单词
                        QString word = tchr;

                        // 追加新单词
                        d->unselectWords.append(word);
                    }
                    else
                    {
                        // 新单词
                        QString word = d->unselectWords.last() + tchr;

                        // 是否单词缩写或完整单词
                        if (d->isWord(word) && !(d->bSeperatePhraseByUser))
                        {
                            // 删除原最后一个单词
                            d->unselectWords.pop_back();

                            // 追加新单词
                            d->unselectWords.append(word);
                        }
                        else
                        {
                            // 追加新单词
                            d->unselectWords.append(tchr);
                        }

                        // 用户主动分词，只生效当前一次
                        d->bSeperatePhraseByUser = false;
                    }
                }
            }
        }
        else
        {
            ret = false;
        }
    }

    // 发送信号
    if (ret)
    {
        // 输入变化处理
        this->onInputChanged();
    }

    return ret;
}

// 加载词库
void PinYin::loadUser(const QString& path)
{
    qDebug() << "PinYin loadUser" << path;

    //
    // 初始化（清空现有词组，并统一预申请哈希表所占内存，降低解析过程中频繁申请所带来的资源消耗）
    //
    // 词组（正向，拼音->汉字）
    d->userPhrases.clear();
    d->userPhrases.reserve(1000);
    // 单词（正向，拼音->汉字）
    d->userWords.clear();
    d->userWords.reserve(500);
    // 词组（反向，汉字->拼音）
    // 多音字，存在多个拼音
    d->userPinyins.clear();
    d->userPinyins.reserve(1000);

    //
    // 重新加载用户词库
    //
    QStringList lines = d->load(path + "/ime/pinyin_user.dic");

    // 按行解析
    foreach (QString line, lines)
    {
        // 行首为拼音，拼音简写，拼音后面为该拼音对应的全部汉字或词组
        QStringList splits = d->localSplit(line, ",", 30);
        if (splits.count() < 3)
        {
            qDebug() << "PinYin load, invalid line: " << line;
            continue;
        }

        QString pinyin = splits.first().toLower();    // 拼音字符串
        splits = splits.mid(2);               // 当前拼音对应的所有汉字或词组

        // 存储汉字或词组
        if (splits.first().length() == 1)
        {
            // 组装（拼音->单个汉字）哈希表
            d->userWords[pinyin] = splits;
        }
        else
        {
            // 组装（拼音->汉字词组）哈希表
            d->userPhrases[pinyin] = splits;
        }

        // 汉字与其对应拼音，包含多音字
        for (int i = 0; i < splits.count(); i++)
        {
            d->userPinyins[splits.at(i)].append(pinyin);
        }
    }

    // 解析完成后根据实际情况设置哈希表大小，避免预申请时的内存浪费
    d->userWords.reserve(d->userWords.count());
    d->userPhrases.reserve(d->userPhrases.count());
    d->userPinyins.reserve(d->userPinyins.count());
}

void PinYin::loadSystem(const QString& path)
{
    qDebug() << "PinYin loadSystem" << path;

    //
    // 初始化（清空现有词组，并统一预申请哈希表所占内存，降低解析过程中频繁申请所带来的资源消耗）
    //
    // 词组（正向，拼音->汉字）
    d->systemPhrases.clear();
    d->systemPhrases.reserve(90000);
    // 单词（正向，拼音->汉字）
    d->systemWords.clear();
    d->systemWords.reserve(500);
    // 词组（反向，汉字->拼音）
    // 多音字，存在多个拼音
    d->systemPinyins.clear();
    d->systemPinyins.reserve(130000);

    //
    // 重新加载系统词库
    //
    QStringList lines = d->load(path + "/ime/pinyin.dic");

    // 按行解析
    foreach (QString line, lines)
    {
        // 行首为拼音，拼音简写，拼音后面为该拼音对应的全部汉字或词组
        QStringList splits = d->localSplit(line, ",", 30);
        if (splits.count() < 3)
        {
            qDebug() << "PinYin load, invalid line: " << line;
            continue;
        }

        QString pinyin = splits.first().toLower();    // 拼音字符串
        splits = splits.mid(2);               // 当前拼音对应的所有汉字或词组

        // 存储汉字或词组
        if (splits.first().length() == 1)
        {
            // 组装（拼音->单个汉字）哈希表
            d->systemWords[pinyin] = splits;
        }
        else
        {
            // 组装（拼音->汉字词组）哈希表
            d->systemPhrases[pinyin] = splits;
        }

        // 汉字与其对应拼音，包含多音字
        for (int i = 0; i < splits.count(); i++)
        {
            d->systemPinyins[splits.at(i)].append(pinyin);
        }
    }

    // 解析完成后根据实际情况设置哈希表大小，避免预申请时的内存浪费
    d->systemWords.reserve(d->systemWords.count());
    d->systemPhrases.reserve(d->systemPhrases.count());
    d->systemPinyins.reserve(d->systemPinyins.count());
}

// 选词选中
void PinYin::onPhraseSelected(const QString& phrase)
{
    // 汉字存在多音字
    QStringList pinyins = d->systemPinyins.value(phrase);
    pinyins.append(d->userPinyins.value(phrase));

    // 更新候选单词
    // 从候选词组中剔除已经选择汉字对应的拼音
    QStringList words = d->unselectWords;

    // 候选词为u、i、v
    if (pinyins.isEmpty() && (phrase.compare("u") == 0 
        || phrase.compare("i") == 0 || phrase.compare("v") == 0
        || d->isUpperString(phrase)))
    {
        words.removeOne(phrase);
    }
    else
    {
        // 多音字处理
        if (pinyins.count() >= 2)
        {
            foreach (QString word, d->unselectWords)
            {
                bool bMatched = false;
                foreach (QString pinyin, pinyins)
                {
                    if (pinyin.startsWith(word))
                    {
                        bMatched = true;
                        d->seletectedPinyin.append(word);
                        words.removeOne(word);
                        pinyins.removeOne(pinyin);
                        break;
                    }
                }

                if (bMatched)
                {
                    break;
                }
            }
        }
        else
        {
            pinyins = pinyins.join("").split("'");
            foreach (QString word, d->unselectWords)
            {
                bool match = false;
                foreach (QString pinyin, pinyins)
                {
                    if (pinyin.startsWith(word))
                    {
                        match = true;

                        // 候选单词组和已选词组中都剔除已经选择的单词
                        d->seletectedPinyin.append(word);
                        words.removeOne(word);
                        pinyins.removeOne(pinyin);
                        break;
                    }
                }

                if (!match)
                {
                    break;
                }
            }
        }
    }

    d->unselectWords = words;

    // 更新已选词组
    d->selectPhrases.append(phrase);

    // 输入变化处理
    this->onInputChanged();
}

// 拼音显示区域满
void PinYin::onPinyinDisplayRegionFull(void)
{
    d->bPinyinDisplayRegionFull = true;
}

// 输入变化
void PinYin::onInputChanged()
{
    // 候选词组
    QStringList candidatePhrases;

    if (d->unselectWords.isEmpty())
    {
        // 录入结束

        // 发送信号
        QString phrases = d->selectPhrases.join("");
        // 未选中的拼音输入后为小写，与拼音小写显示保持一致
        emit inputFinished(phrases); 

        // 清空已选词组
        d->selectPhrases.clear();
        // 清空待选单词
        d->unselectWords.clear();
        // 清空已选拼音
        d->seletectedPinyin.clear();

        d->bPinyinDisplayRegionFull = false;
        d->bSeperatePhraseByUser = false;
    }
    else
    {
        // 计算候选词组
        candidatePhrases = d->getCandidatePhrases(d->unselectWords);
    }

    // 用户主动分词，并且已经存在用户输入的拼音时，需要在已输入的拼音末尾添加分词符号
    QStringList phraseAndPinyinList = d->selectPhrases;
    if (d->bSeperatePhraseByUser && d->unselectWords.count() > 0)
    {
        QStringList unselectedPinyinList = d->unselectWords;
        QString strLast = unselectedPinyinList.last();
        unselectedPinyinList.removeLast();
        unselectedPinyinList.append(strLast + "'");

        phraseAndPinyinList += unselectedPinyinList;
    }
    else
    {
        phraseAndPinyinList += d->unselectWords;
    }

    // 发送信号
    emit phrasesChanged(phraseAndPinyinList, candidatePhrases);
}