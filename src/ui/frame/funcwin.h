#ifndef _FUNC_WIN_H_
#define _FUNC_WIN_H_


#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class ReagentWidget;


// 功能界面（顶部，中部，底部状态栏）
class FuncWin : public QWidget
{
    Q_OBJECT

public:
    FuncWin(QWidget* parent = 0);
    virtual ~FuncWin();

    // 窗口标识
    QString wId() const;
    void setWId(const QString& wId);

    // 吸样键按下
    virtual void onAbsorbKeyDown();

signals:
    // 切换到功能窗口
    void toFuncWin(FuncWin* funcWin);

protected:
    // 界面字符串
    virtual void setWindowText();

    // 创建状态条
    virtual void createStatusBar();

    // 界面使能
    virtual void enableWindow(bool enable);
    // 吸样键使能
    virtual void enableAbsorbKey(bool enable);

    // 启动时序失败处理
    virtual void onRunTimeseqFail(int ret);

    // 切换到功能窗口
    virtual void switchToFuncWin(FuncWin* funcWin);

protected:
    // 界面字符串
    virtual QString getString(const QString& ids);

    virtual void setText(QLabel* widget, const QString& ids);
    virtual void setText(QLineEdit* widget, const QString& ids);
    virtual void setText(QAbstractButton* widget, const QString& ids);

private slots:
    // 按钮点击
    void onBtnMenuClicked();
    void onBtnFaultClicked();
    void onReagentWidgetClicked();

    // 故障变化
    void onFaultChanged(const QList<int>& faults);

protected:
    // 窗口标识
    QString winId;

    // 顶部状态栏
    QLabel* lbLogo; // LOGO标签
    QPushButton* pbMenu; // 菜单按钮

    // 底部状态栏
    QPushButton* pbFault; // 当前故障
    ReagentWidget* reagentWidget; // 试剂状态
};


#endif // _FUNC_WIN_H_
