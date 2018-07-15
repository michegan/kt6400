#include <QHash>
#include <QFile>
#include <QtDebug>
#include <QTextStream>

#include "pinyin.h"


// ����ѡ����
#define MAX_CANDIDATES  (200)


class PinYinPrivate
{
public:
    PinYinPrivate();
    ~PinYinPrivate();

    // �Ƿ�����
    bool isPrint(int chr);

    // �Ƿ񵥴�
    bool isWord(const QString& text);

    // �ض�
    QString trim(const QString& text);

    // ����
    QStringList load(const QString& filename);

    // ��ѡ����
    QStringList getCandidatePhrases(const QStringList& words);

    // ���ݷָ����ض��ַ�������split����������ͬ���˴���д�����Ч��
    QStringList localSplit(const QString& strSrc, const QString& strSep, int iSize);

    // �ַ������Ƿ�ֻ�����˴�д��ĸ
    bool isUpperString(QString strSrc);

public:
    // ��ѡ����
    QStringList selectPhrases;
    // δѡ����
    QStringList unselectWords;
    // ��ѡƴ��
    QStringList seletectedPinyin;

public:
    // ���飨����ƴ��->���֣�
    QHash<QString, QStringList> userPhrases;
    QHash<QString, QStringList> systemPhrases;
    // ���ʣ�����ƴ��->���֣�
    QHash<QString, QStringList> userWords;
    QHash<QString, QStringList> systemWords;
    // ���飨���򣬺���->ƴ����
    // �����֣����ڶ��ƴ��
    QHash<QString, QStringList> userPinyins;
    QHash<QString, QStringList> systemPinyins;

    // �û������ִ�
    bool bSeperatePhraseByUser;

    // ƴ����ʾ������
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

// �Ƿ�ɴ�ӡ
bool PinYinPrivate::isPrint(int chr)
{
    return (0x20 < chr && chr < 0x7F);
}

// �Ƿ񵥴�
bool PinYinPrivate::isWord(const QString& text)
{
    bool ret = false;

    // ϵͳ�ʿ�
    QStringList words = this->systemWords.keys();
    // �û��ʿ�
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

// �ض�
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

// ���ݷָ����ض��ַ�������split����������ͬ���˴���д�����Ч��
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

// �ַ������Ƿ�ֻ�����˴�д��ĸ
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

// ����
QStringList PinYinPrivate::load(const QString& filename)
{
    QStringList lines;
    QFile file(filename);

    qDebug() << "PinYin load" << filename;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // һ���Լ����ı����ݣ����ٴ�ѭ������������Դ����
        QTextStream stream(&file);
        QString line = stream.readAll();

        // �Զ�����
        lines = this->localSplit(line, "\n", 170000);

        file.close();
    }
    else
    {
        qWarning() << "PinYinPrivate load open fail";
    }

    return lines;
}

// ��ѡ����
QStringList PinYinPrivate::getCandidatePhrases(const QStringList& words)
{
    QStringList phrases;

    // ���飨ȫƥ�䣩
    {
        for (int length = words.length(); length > 0; length--)
        {
            QStringList list = words.mid(0, length);
            // �������Ҫ�ڴ����ϣ���в��Ҷ�Ӧ�Ĵ���
            if (list.count() >= 2)
            {
                QString key = list.join("'");

                // �û��ʿ�
                if (!(this->userPhrases.value(key, QStringList()).isEmpty()))
                {
                    phrases.append(this->userPhrases.value(key));
                }
                // ϵͳ�ʿ�
                if (!(this->systemPhrases.value(key, QStringList()).isEmpty()))
                {
                    phrases.append(this->systemPhrases.value(key));
                }
            }
        }
    }

    // ���ʣ�ȫƥ�䣩
    {
        QString word = words.first();

        // �û��ʿ�
        if (!(this->userWords.value(word, QStringList()).isEmpty()))
        {
            phrases.append(this->userWords.value(word));
        }
        // ϵͳ�ʿ�
        if (!(this->systemWords.value(word, QStringList()).isEmpty()))
        {
            phrases.append(this->systemWords.value(word));
        }
    }

    // ���ǰ�涼û��ƥ�䵽����ģ��ƥ��
    if (phrases.isEmpty())
    {
        QString word = words.first();

        // �û��ʿ�
        QStringList keys = this->userWords.keys();
        foreach (QString key, keys)
        {
            if (key.startsWith(word))
            {
                phrases.append(this->userWords.value(key));
                break;
            }
        }

        // ϵͳ�ʿ�
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

    // ������i��u��v�޷��ҵ������Ӧ�ĺ�ѡ���ֻ���飬
    // ��ʱֱ�ӽ�����ĸ��Ϊ��ѡ��
    QString strUnselectedWord = words.first().trimmed();
    if (phrases.isEmpty() && (strUnselectedWord.compare("u") == 0 
        || strUnselectedWord.compare("i") == 0 || strUnselectedWord.compare("v") == 0))
    {
        phrases.append(strUnselectedWord);
    }

    // �����д��ĸ�ַ���,ֱ����Ϊ��ѡ��
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

// �������
void PinYin::clear()
{
    // �����ѡ����
    d->selectPhrases.clear();
    // ��մ�ѡ����
    d->unselectWords.clear();
    // �����ѡƴ��
    d->seletectedPinyin.clear();

    // ƴ����ʾ������
    d->bPinyinDisplayRegionFull = false;
    d->bSeperatePhraseByUser = false;
}

// ���ַ�
bool PinYin::onNewChar(int chr)
{
    bool ret = true;

    if (Qt::Key_Enter == chr || Qt::Key_Return == chr)
    {
        // ѡ��
        if (d->unselectWords.isEmpty() && d->selectPhrases.isEmpty())
        {
            // �������ѡ�ʣ������ϲ㴦��
            ret = false;
        }
        else
        {
            // ȫ����ѡ����ת��Ϊ��ѡ����
            d->selectPhrases.append(d->unselectWords);

            // ��մ�ѡ����
            d->unselectWords.clear();
        }
    }
    else if (Qt::Key_Backspace == chr)
    {
        d->bPinyinDisplayRegionFull = false;

        // ɾ����ǰ¼��
        if (d->unselectWords.isEmpty())
        {
            // �޵��ʿ�ɾ���������ϲ㴦��
            ret = false;
        }
        else if (d->bSeperatePhraseByUser)
        {
            d->bSeperatePhraseByUser = false;
        }
        else
        {
            // ��ѡ�д���ʱ
            if (d->seletectedPinyin.isEmpty())
            {
                // ���һ������
                QString last = d->unselectWords.last();

                // �ض�
                last = d->trim(last);

                // ɾ�����һ������
                d->unselectWords.pop_back();

                // ����׷���µ���
                if (!last.isEmpty())
                {
                    d->unselectWords.append(last);
                }
            }
            else
            {
                // ȥ�����һ����ѡ����
                QString strLastPhrase =  d->selectPhrases.last();
                d->selectPhrases.removeLast();

                // �û�ѡ��Ϊ����ʱ����Ҫ�������Ӧ��ƴ��ȫ�������ѡƴ����
                for (int i=0; i<strLastPhrase.count(); i++)
                {
                    // ����һ����ѡƴ�������ѡƴ������
                    d->unselectWords.push_front(d->seletectedPinyin.last());
                    // ȥ����һ����ѡƴ��
                    d->seletectedPinyin.removeLast();
                }
            }
        }
    }
    else if (Qt::Key_Clear == chr)
    {
        // ��յ�ǰ¼��
        // �����ѡ����
        d->selectPhrases.clear();
        // ��մ�ѡ����
        d->unselectWords.clear();
        // �����ѡƴ��
        d->seletectedPinyin.clear();

        d->bPinyinDisplayRegionFull = false;
        d->bSeperatePhraseByUser = false;
    }
    else if (QChar(chr) == QChar('\'') && !d->unselectWords.isEmpty())
    {
        // ����ƴ���ָ���
        d->bSeperatePhraseByUser = true;
        ret = true;
    }
    else if (QChar(chr).isNumber() || QChar(chr).isSymbol() || QChar(chr).isPunct())
    {
        // ���������֣�������
        ret = false;
    }
    else if (d->unselectWords.isEmpty() && d->selectPhrases.isEmpty() && QChar(chr).isUpper())
    {
        // ֱ�������д��ĸ�������ϲ㴦��
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
                // �����û�����Ĵ�д��ĸ
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
                                // ɾ��ԭ���һ������
                                d->unselectWords.pop_back();

                                // ׷���µ���
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
                        // �µ���
                        QString word = tchr;

                        // ׷���µ���
                        d->unselectWords.append(word);
                    }
                    else
                    {
                        // �µ���
                        QString word = d->unselectWords.last() + tchr;

                        // �Ƿ񵥴���д����������
                        if (d->isWord(word) && !(d->bSeperatePhraseByUser))
                        {
                            // ɾ��ԭ���һ������
                            d->unselectWords.pop_back();

                            // ׷���µ���
                            d->unselectWords.append(word);
                        }
                        else
                        {
                            // ׷���µ���
                            d->unselectWords.append(tchr);
                        }

                        // �û������ִʣ�ֻ��Ч��ǰһ��
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

    // �����ź�
    if (ret)
    {
        // ����仯����
        this->onInputChanged();
    }

    return ret;
}

// ���شʿ�
void PinYin::loadUser(const QString& path)
{
    qDebug() << "PinYin loadUser" << path;

    //
    // ��ʼ����������д��飬��ͳһԤ�����ϣ����ռ�ڴ棬���ͽ���������Ƶ����������������Դ���ģ�
    //
    // ���飨����ƴ��->���֣�
    d->userPhrases.clear();
    d->userPhrases.reserve(1000);
    // ���ʣ�����ƴ��->���֣�
    d->userWords.clear();
    d->userWords.reserve(500);
    // ���飨���򣬺���->ƴ����
    // �����֣����ڶ��ƴ��
    d->userPinyins.clear();
    d->userPinyins.reserve(1000);

    //
    // ���¼����û��ʿ�
    //
    QStringList lines = d->load(path + "/ime/pinyin_user.dic");

    // ���н���
    foreach (QString line, lines)
    {
        // ����Ϊƴ����ƴ����д��ƴ������Ϊ��ƴ����Ӧ��ȫ�����ֻ����
        QStringList splits = d->localSplit(line, ",", 30);
        if (splits.count() < 3)
        {
            qDebug() << "PinYin load, invalid line: " << line;
            continue;
        }

        QString pinyin = splits.first().toLower();    // ƴ���ַ���
        splits = splits.mid(2);               // ��ǰƴ����Ӧ�����к��ֻ����

        // �洢���ֻ����
        if (splits.first().length() == 1)
        {
            // ��װ��ƴ��->�������֣���ϣ��
            d->userWords[pinyin] = splits;
        }
        else
        {
            // ��װ��ƴ��->���ִ��飩��ϣ��
            d->userPhrases[pinyin] = splits;
        }

        // ���������Ӧƴ��������������
        for (int i = 0; i < splits.count(); i++)
        {
            d->userPinyins[splits.at(i)].append(pinyin);
        }
    }

    // ������ɺ����ʵ��������ù�ϣ���С������Ԥ����ʱ���ڴ��˷�
    d->userWords.reserve(d->userWords.count());
    d->userPhrases.reserve(d->userPhrases.count());
    d->userPinyins.reserve(d->userPinyins.count());
}

void PinYin::loadSystem(const QString& path)
{
    qDebug() << "PinYin loadSystem" << path;

    //
    // ��ʼ����������д��飬��ͳһԤ�����ϣ����ռ�ڴ棬���ͽ���������Ƶ����������������Դ���ģ�
    //
    // ���飨����ƴ��->���֣�
    d->systemPhrases.clear();
    d->systemPhrases.reserve(90000);
    // ���ʣ�����ƴ��->���֣�
    d->systemWords.clear();
    d->systemWords.reserve(500);
    // ���飨���򣬺���->ƴ����
    // �����֣����ڶ��ƴ��
    d->systemPinyins.clear();
    d->systemPinyins.reserve(130000);

    //
    // ���¼���ϵͳ�ʿ�
    //
    QStringList lines = d->load(path + "/ime/pinyin.dic");

    // ���н���
    foreach (QString line, lines)
    {
        // ����Ϊƴ����ƴ����д��ƴ������Ϊ��ƴ����Ӧ��ȫ�����ֻ����
        QStringList splits = d->localSplit(line, ",", 30);
        if (splits.count() < 3)
        {
            qDebug() << "PinYin load, invalid line: " << line;
            continue;
        }

        QString pinyin = splits.first().toLower();    // ƴ���ַ���
        splits = splits.mid(2);               // ��ǰƴ����Ӧ�����к��ֻ����

        // �洢���ֻ����
        if (splits.first().length() == 1)
        {
            // ��װ��ƴ��->�������֣���ϣ��
            d->systemWords[pinyin] = splits;
        }
        else
        {
            // ��װ��ƴ��->���ִ��飩��ϣ��
            d->systemPhrases[pinyin] = splits;
        }

        // ���������Ӧƴ��������������
        for (int i = 0; i < splits.count(); i++)
        {
            d->systemPinyins[splits.at(i)].append(pinyin);
        }
    }

    // ������ɺ����ʵ��������ù�ϣ���С������Ԥ����ʱ���ڴ��˷�
    d->systemWords.reserve(d->systemWords.count());
    d->systemPhrases.reserve(d->systemPhrases.count());
    d->systemPinyins.reserve(d->systemPinyins.count());
}

// ѡ��ѡ��
void PinYin::onPhraseSelected(const QString& phrase)
{
    // ���ִ��ڶ�����
    QStringList pinyins = d->systemPinyins.value(phrase);
    pinyins.append(d->userPinyins.value(phrase));

    // ���º�ѡ����
    // �Ӻ�ѡ�������޳��Ѿ�ѡ���ֶ�Ӧ��ƴ��
    QStringList words = d->unselectWords;

    // ��ѡ��Ϊu��i��v
    if (pinyins.isEmpty() && (phrase.compare("u") == 0 
        || phrase.compare("i") == 0 || phrase.compare("v") == 0
        || d->isUpperString(phrase)))
    {
        words.removeOne(phrase);
    }
    else
    {
        // �����ִ���
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

                        // ��ѡ���������ѡ�����ж��޳��Ѿ�ѡ��ĵ���
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

    // ������ѡ����
    d->selectPhrases.append(phrase);

    // ����仯����
    this->onInputChanged();
}

// ƴ����ʾ������
void PinYin::onPinyinDisplayRegionFull(void)
{
    d->bPinyinDisplayRegionFull = true;
}

// ����仯
void PinYin::onInputChanged()
{
    // ��ѡ����
    QStringList candidatePhrases;

    if (d->unselectWords.isEmpty())
    {
        // ¼�����

        // �����ź�
        QString phrases = d->selectPhrases.join("");
        // δѡ�е�ƴ�������ΪСд����ƴ��Сд��ʾ����һ��
        emit inputFinished(phrases); 

        // �����ѡ����
        d->selectPhrases.clear();
        // ��մ�ѡ����
        d->unselectWords.clear();
        // �����ѡƴ��
        d->seletectedPinyin.clear();

        d->bPinyinDisplayRegionFull = false;
        d->bSeperatePhraseByUser = false;
    }
    else
    {
        // �����ѡ����
        candidatePhrases = d->getCandidatePhrases(d->unselectWords);
    }

    // �û������ִʣ������Ѿ������û������ƴ��ʱ����Ҫ���������ƴ��ĩβ��ӷִʷ���
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

    // �����ź�
    emit phrasesChanged(phraseAndPinyinList, candidatePhrases);
}