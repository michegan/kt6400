#ifndef _INPUT_CONTEXT_H_
#define _INPUT_CONTEXT_H_


#include <QInputContext>

#include "libkeyboard.h"


class InputContextPrivate;


// 输入上下文
class KEYBOARD_EXPORT InputContext : public QInputContext
{
    Q_OBJECT

public:
    InputContext(QObject* parent = 0);
    virtual ~InputContext();

    // 开关状态
    bool enabled() const;
    void setEnabled(bool enabled);

    // 最大尺寸
    void setMaxSize(const QSize& size);

    // 资源路径
    QString rootPath();
    void setRootPath(const QString& path);

    // 语言代码
    void setLanguage(const QString& language);

    // 设置小数点字符
    void setDecimalPointChar(int chr = Qt::Key_Period);

    // 加载用户词库
    void loadUserPhrase();

public:
    // 状态重置
    virtual void reset();

    // 语言代码
    virtual QString language();

    // 是否组合
    virtual bool isComposing() const;

    // 标识
    virtual QString identifierName();

    // 事件处理
    virtual bool filterEvent(const QEvent* event);

    // 过滤事件
    virtual bool eventFilter(QObject *obj, QEvent *event);

public:
    // 按键处理
    bool onKeyReleaseEvent(int key);

    // 鼠标点击
    void onMouseButtonPressed(const QPoint& globalPos);

private:
    // 切换到软键盘
    void switchToKeyBoard(int chr);

private slots:
    // 输入按键
    void onButtonClicked(int chr);
    void onButtonClicked(const QString& text);

    // 关闭按键
    void onCloseButtonClicked(int chr);
    // 输入按键
    void onInputButtonClicked(int chr);
    void onInputButtonClicked(const QString& text);
    // 功能按键
    void onFunctionButtonClicked(int chr);

private:
    InputContextPrivate* d;
};


#endif  // _INPUT_CONTEXT_H_