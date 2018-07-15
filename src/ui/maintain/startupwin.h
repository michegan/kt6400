#ifndef _STARTUP_WIN_H_
#define _STARTUP_WIN_H_


#include <QTimer>

#include "funcwin.h"
#include "sampleinfo.h"
#include "ui_startupwin.h"

class Count;
class AsyncTimeseq;


// ������
class StartupWin : public FuncWin
{
    Q_OBJECT

public:
    StartupWin(QWidget* parent = 0);
    virtual ~StartupWin();

protected:
    // �����ַ���
    virtual void setWindowText();

protected:
    // �¼�����
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // ��ʱ����ʱ
    void onTimerOut();
    void onStartupTimeOut();

    // �㷨����
    void onCountAlgFinished();
    // ��������
    void onCountFinished(bool result);

    // ʱ�����
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // ��������
    void onStartupFinished();

    // ���¿���״̬
    void setStartupState(int state);

private:
    // ���ȶ�ʱ��
    QTimer* timer;

    // ��������
    Count* count;

    // ����Ԫ��
    Ui::StartupWin ui;

    // ������Ϣ
    SampleInfo sampleInfo;

    // ʱ��ִ����
    AsyncTimeseq* timeseq;
};


#endif // _STARTUP_WIN_H_
