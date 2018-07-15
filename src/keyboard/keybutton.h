#ifndef _KEY_BUTTON_H_
#define _KEY_BUTTON_H_


#include <QImage>
#include <QPushButton>


class KeyButtonPrivate;


// 键盘按键
class KeyButton : public QPushButton
{
    Q_OBJECT

public:
    KeyButton(QWidget* parent);
    virtual ~KeyButton();

    // 字符
    int chr1() const;
    int chr2() const;
    void setChr(int chr1, int chr2 = 0);

    // 是否显示字符
    bool showChr() const;
    void setShowChr(bool showChr);

    // 背景图
    void setImage(const QString& image);

protected:
    // 重绘事件
    virtual void paintEvent(QPaintEvent* event);

    // 双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

private:
    KeyButtonPrivate* d;
};


#endif // _KEY_BUTTON_H_