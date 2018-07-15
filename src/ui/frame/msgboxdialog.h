#ifndef _MSG_BOX_DIALOG_H_
#define _MSG_BOX_DIALOG_H_


#include <QMessageBox>

#include "dialog.h"
#include "ui_msgboxdialog.h"

class MsgBoxDialogPrivate;


// ��Ϣ�Ի���
class MsgBoxDialog : public Dialog
{
    Q_OBJECT

public:
    MsgBoxDialog(const QString& text, QMessageBox::StandardButton btn1, 
                 QMessageBox::StandardButton btn2 = QMessageBox::NoButton, QWidget* parent = 0);
    virtual ~MsgBoxDialog();

    // �û�ѡ��
    QMessageBox::StandardButton select() const;

protected:
    // �����ַ���
    virtual void setWindowText();

protected:
    // �ߴ�仯
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    // ��ť���
    void onBtnButton1Clicked();
    void onBtnButton2Clicked();

private:
    // ��ť�ı�
    QString buttonText(QMessageBox::StandardButton btn);

private:
    // ����
    Ui::MsgBoxDialog ui;

    // ��ťѡ��
    QMessageBox::StandardButton button;
    QMessageBox::StandardButton button1;
    QMessageBox::StandardButton button2;
};


#endif // _MSG_BOX_DIALOG_H_