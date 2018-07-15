#ifndef _INPUT_CONTEXT_H_
#define _INPUT_CONTEXT_H_


#include <QInputContext>

#include "libkeyboard.h"


class InputContextPrivate;


// ����������
class KEYBOARD_EXPORT InputContext : public QInputContext
{
    Q_OBJECT

public:
    InputContext(QObject* parent = 0);
    virtual ~InputContext();

    // ����״̬
    bool enabled() const;
    void setEnabled(bool enabled);

    // ���ߴ�
    void setMaxSize(const QSize& size);

    // ��Դ·��
    QString rootPath();
    void setRootPath(const QString& path);

    // ���Դ���
    void setLanguage(const QString& language);

    // ����С�����ַ�
    void setDecimalPointChar(int chr = Qt::Key_Period);

    // �����û��ʿ�
    void loadUserPhrase();

public:
    // ״̬����
    virtual void reset();

    // ���Դ���
    virtual QString language();

    // �Ƿ����
    virtual bool isComposing() const;

    // ��ʶ
    virtual QString identifierName();

    // �¼�����
    virtual bool filterEvent(const QEvent* event);

    // �����¼�
    virtual bool eventFilter(QObject *obj, QEvent *event);

public:
    // ��������
    bool onKeyReleaseEvent(int key);

    // �����
    void onMouseButtonPressed(const QPoint& globalPos);

private:
    // �л��������
    void switchToKeyBoard(int chr);

private slots:
    // ���밴��
    void onButtonClicked(int chr);
    void onButtonClicked(const QString& text);

    // �رհ���
    void onCloseButtonClicked(int chr);
    // ���밴��
    void onInputButtonClicked(int chr);
    void onInputButtonClicked(const QString& text);
    // ���ܰ���
    void onFunctionButtonClicked(int chr);

private:
    InputContextPrivate* d;
};


#endif  // _INPUT_CONTEXT_H_