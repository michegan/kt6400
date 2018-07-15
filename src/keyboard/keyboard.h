#ifndef _KEY_BOARD_H_
#define _KEY_BOARD_H_


#include <QWidget>


class KeyButton;
class KeyBoardPrivate;


// 软键盘
class KeyBoard : public QWidget
{
    Q_OBJECT

public:
    KeyBoard(int id);
    virtual ~KeyBoard();

    // 标识
    int id() const;

    // 界面风格
    void setYSpace(int space);
    void setYMargin(int margin);

    // CAPS状态
    virtual bool capslock() const;

    // 清除输入
    virtual void clear();

    // 按键处理
    virtual bool onKeyReleaseEvent(int key);

signals:
    // 输入按键
    void clicked(int chr);
    void clicked(const QString& text);

protected:
    // 换行
    void newLine(int x = 10);

    // 按钮
    KeyButton* button(int chr1) const;

    // 添加字符按键
    void addChrButton(int chr1, int chr2 = 0, int width = 49);
    // 添加图片按键
    void addImageButton(const QString& image, int width, bool showChr = false);
    void addImageButton(int chr1, const QString& image, int width, bool showChr = false);

private slots:
    // 信号映射
    void onSignalMapped(QWidget* widget);

    // 大小写锁定处理
    void onCapslockBtnChecked(bool bChecked);

private:
    // 添加按钮
    void addButton(KeyButton* button);

private:
    KeyBoardPrivate* d;
};


#endif // _KEY_BOARD_H_