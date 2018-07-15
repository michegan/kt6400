#ifndef _PIN_YIN_H_
#define _PIN_YIN_H_


#include <QStringList>


class PinYinPrivate;


// 拼音输入法
class PinYin : public QObject
{
    Q_OBJECT

public:
    PinYin();
    virtual ~PinYin();

    // 清除输入
    virtual void clear();

    // 新字符
    virtual bool onNewChar(int chr);

    // 加载词库
    virtual void loadUser(const QString& path);
    virtual void loadSystem(const QString& path);

public slots:
    // 选词选中
    virtual void onPhraseSelected(const QString& phrase);

    // 拼音显示区域满
    virtual void onPinyinDisplayRegionFull(void);

signals:
    // 输入结束
    void inputFinished(const QString& text);

    // 词组变化
    void phrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases);

private:
    // 输入变化
    void onInputChanged();

private:
    PinYinPrivate* d;
};


#endif // _PIN_YIN_H_