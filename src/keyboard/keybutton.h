#ifndef _KEY_BUTTON_H_
#define _KEY_BUTTON_H_


#include <QImage>
#include <QPushButton>


class KeyButtonPrivate;


// ���̰���
class KeyButton : public QPushButton
{
    Q_OBJECT

public:
    KeyButton(QWidget* parent);
    virtual ~KeyButton();

    // �ַ�
    int chr1() const;
    int chr2() const;
    void setChr(int chr1, int chr2 = 0);

    // �Ƿ���ʾ�ַ�
    bool showChr() const;
    void setShowChr(bool showChr);

    // ����ͼ
    void setImage(const QString& image);

protected:
    // �ػ��¼�
    virtual void paintEvent(QPaintEvent* event);

    // ˫���¼�
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

private:
    KeyButtonPrivate* d;
};


#endif // _KEY_BUTTON_H_