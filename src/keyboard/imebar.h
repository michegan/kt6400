#ifndef _IME_BAR_H_
#define _IME_BAR_H_


#include <QWidget>

#include "libkeyboard.h"


class ImeBarPrivate;


// 输入条
class KEYBOARD_EXPORT ImeBar : public QWidget
{
    Q_OBJECT

public:
    ImeBar();
    virtual ~ImeBar();

    // 清除输入
    void clear();

    // 处理输入
    bool processInput(int key);

signals:
    // 选词
    void phraseSelected(const QString& phrase);

    // 拼音显示区域满
    void pinyinDisplayRegionFull();

public slots:
    // 词组变化
    void onPhrasesChanged(const QStringList& selectPhrases, const QStringList& candidatePhrases);

protected:
    // 绘制事件
    virtual void paintEvent(QPaintEvent* event);

    // 鼠标事件
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private slots:
    // 按钮点击
    void onBtnPageUpClicked();
    void onBtnPageDownClicked();

private:
    // 外部选词
    bool selectFirst();

    // 数字选词
    bool selectPhraseByNumber(int key);

    // 候选词向前翻页
    bool turnPageUp();

    // 候选词向后翻页
    bool turnPageDown();

private:
    ImeBarPrivate* d;
};


#endif // _IME_BAR_H_