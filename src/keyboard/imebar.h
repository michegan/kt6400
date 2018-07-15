#ifndef _IME_BAR_H_
#define _IME_BAR_H_


#include <QWidget>

#include "libkeyboard.h"


class ImeBarPrivate;


// ������
class KEYBOARD_EXPORT ImeBar : public QWidget
{
    Q_OBJECT

public:
    ImeBar();
    virtual ~ImeBar();

    // �������
    void clear();

    // ��������
    bool processInput(int key);

signals:
    // ѡ��
    void phraseSelected(const QString& phrase);

    // ƴ����ʾ������
    void pinyinDisplayRegionFull();

public slots:
    // ����仯
    void onPhrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases);

protected:
    // �����¼�
    virtual void paintEvent(QPaintEvent* event);

    // ����¼�
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private slots:
    // ��ť���
    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

private:
    // �ⲿѡ��
    bool selectFirst();

    // ����ѡ��
    bool selectPhraseByNumber(int key);

    // ��ѡ����ǰ��ҳ
    bool turnPageUp();

    // ��ѡ�����ҳ
    bool turnPageDown();

private:
    ImeBarPrivate* d;
};


#endif // _IME_BAR_H_