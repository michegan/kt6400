#ifndef _PIN_YIN_H_
#define _PIN_YIN_H_


#include <QStringList>


class PinYinPrivate;


// ƴ�����뷨
class PinYin : public QObject
{
    Q_OBJECT

public:
    PinYin();
    virtual ~PinYin();

    // �������
    virtual void clear();

    // ���ַ�
    virtual bool onNewChar(int chr);

    // ���شʿ�
    virtual void loadUser(const QString& path);
    virtual void loadSystem(const QString& path);

public slots:
    // ѡ��ѡ��
    virtual void onPhraseSelected(const QString& phrase);

    // ƴ����ʾ������
    virtual void onPinyinDisplayRegionFull(void);

signals:
    // �������
    void inputFinished(const QString& text);

    // ����仯
    void phrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases);

private:
    // ����仯
    void onInputChanged();

private:
    PinYinPrivate* d;
};


#endif // _PIN_YIN_H_