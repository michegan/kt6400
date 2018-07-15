#ifndef _SHUTDOWN_DIALOG_H_
#define _SHUTDOWN_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_shutdowndialog.h"


// ģʽ�༭�Ի���
class ShutDownDialog : public Dialog
{
    Q_OBJECT

public:
    ShutDownDialog(QWidget* parent = 0);
    virtual ~ShutDownDialog();

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

private:
    // �ػ�����
    int steps;

    // ��ʱ��
    QTimer* timer;

    // ����
    Ui::ShutDownDialog ui;
};


#endif // _SHUTDOWN_DIALOG_H_