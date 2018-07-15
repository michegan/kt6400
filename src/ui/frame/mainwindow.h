#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_


#include <QTimer>
#include <QDialog>

class FuncWin;


// 主界面
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

protected:
    // 按键响应
    virtual void keyPressEvent(QKeyEvent* event);

private slots:
    // 定时器超时
    void onTimerOut();

    // 切换到功能窗口
    void onSwitchToFuncWin(FuncWin* funcWin);

private:
    // 是否响应吸样键
    bool isAbsorbKeyEnabled() const;

private:
    // 定时器
    QTimer* timer;

    // 功能窗口
    FuncWin* funcWin;
};


#endif // _MAIN_WINDOW_H_
