#ifndef _SENSOR_DIALOG_H_
#define _SENSOR_DIALOG_H_


#include <QTimer>

#include "dialog.h"
#include "ui_sensordialog.h"


// ģʽ�༭�Ի���
class SensorDialog : public Dialog
{
    Q_OBJECT

public:
    SensorDialog(QWidget* parent = 0);
    virtual ~SensorDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ʱ����ʱ
    void onTimerOut();

private:
    // ��ʱ��
    QTimer* timer;

    // ����
    Ui::SensorDialog ui;
};


#endif // _SENSOR_DIALOG_H_