#ifndef _STARTUP_WIN_H_
#define _STARTUP_WIN_H_


#include <QTimer>

#include "funcwin.h"
#include "sampleinfo.h"
#include "ui_startupwin.h"

class Count;
class AsyncTimeseq;


// 主界面
class StartupWin : public FuncWin
{
    Q_OBJECT

public:
    StartupWin(QWidget* parent = 0);
    virtual ~StartupWin();

protected:
    // 界面字符串
    virtual void setWindowText();

protected:
    // 事件处理
    virtual void paintEvent(QPaintEvent* event);

private slots:
    // 定时器超时
    void onTimerOut();
    void onStartupTimeOut();

    // 算法结束
    void onCountAlgFinished();
    // 计数结束
    void onCountFinished(bool result);

    // 时序结束
    void onTimeseqFinished(const QString& seqNo, bool result);

private:
    // 开机结束
    void onStartupFinished();

    // 更新开机状态
    void setStartupState(int state);

private:
    // 进度定时器
    QTimer* timer;

    // 计数服务
    Count* count;

    // 界面元素
    Ui::StartupWin ui;

    // 样本信息
    SampleInfo sampleInfo;

    // 时序执行体
    AsyncTimeseq* timeseq;
};


#endif // _STARTUP_WIN_H_
