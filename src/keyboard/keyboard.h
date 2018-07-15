#ifndef _KEY_BOARD_H_
#define _KEY_BOARD_H_


#include <QWidget>


class KeyButton;
class KeyBoardPrivate;


// �����
class KeyBoard : public QWidget
{
    Q_OBJECT

public:
    KeyBoard(int id);
    virtual ~KeyBoard();

    // ��ʶ
    int id() const;

    // ������
    void setYSpace(int space);
    void setYMargin(int margin);

    // CAPS״̬
    virtual bool capslock() const;

    // �������
    virtual void clear();

    // ��������
    virtual bool onKeyReleaseEvent(int key);

signals:
    // ���밴��
    void clicked(int chr);
    void clicked(const QString& text);

protected:
    // ����
    void newLine(int x = 10);

    // ��ť
    KeyButton* button(int chr1) const;

    // ����ַ�����
    void addChrButton(int chr1, int chr2 = 0, int width = 49);
    // ���ͼƬ����
    void addImageButton(const QString& image, int width, bool showChr = false);
    void addImageButton(int chr1, const QString& image, int width, bool showChr = false);

private slots:
    // �ź�ӳ��
    void onSignalMapped(QWidget* widget);

    // ��Сд��������
    void onCapslockBtnChecked(bool bChecked);

private:
    // ��Ӱ�ť
    void addButton(KeyButton* button);

private:
    KeyBoardPrivate* d;
};


#endif // _KEY_BOARD_H_