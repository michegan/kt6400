#ifndef _PROGRESS_DIALOG_H_
#define _PROGRESS_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_progressdialog.h"


// �ֶ�ά���Ի���
class ProgressDialog : public Dialog
{
    Q_OBJECT

public:
    ProgressDialog(QWidget* parent = 0);
    virtual ~ProgressDialog();

    // ִ��
    void exec(float time);

    // �û���ʾ
    void setText(const QString& text);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

private:
    // ���ȶ�ʱ��
    QTimer* timer;

    // ����
    Ui::ProgressDialog ui;
};


#endif // _PROGRESS_DIALOG_H_