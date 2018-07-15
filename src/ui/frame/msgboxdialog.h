#ifndef _MSG_BOX_DIALOG_H_
#define _MSG_BOX_DIALOG_H_


#include <QMessageBox>

#include "dialog.h"
#include "ui_msgboxdialog.h"

class MsgBoxDialogPrivate;


// 消息对话框
class MsgBoxDialog : public Dialog
{
    Q_OBJECT

public:
    MsgBoxDialog(const QString& text, QMessageBox::StandardButton btn1, 
                 QMessageBox::StandardButton btn2 = QMessageBox::NoButton, QWidget* parent = 0);
    virtual ~MsgBoxDialog();

    // 用户选项
    QMessageBox::StandardButton select() const;

protected:
    // 界面字符串
    virtual void setWindowText();

protected:
    // 尺寸变化
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    // 按钮点击
    void onBtnButton1Clicked();
    void onBtnButton2Clicked();

private:
    // 按钮文本
    QString buttonText(QMessageBox::StandardButton btn);

private:
    // 界面
    Ui::MsgBoxDialog ui;

    // 按钮选项
    QMessageBox::StandardButton button;
    QMessageBox::StandardButton button1;
    QMessageBox::StandardButton button2;
};


#endif // _MSG_BOX_DIALOG_H_