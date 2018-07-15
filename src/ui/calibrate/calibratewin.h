#ifndef _CALIBRATE_WIN_H_
#define _CALIBRATE_WIN_H_


#include "para.h"
#include "modes.h"
#include "countfuncwin.h"

#include "ui_calibratewin.h"

class Count;
class CalibrateTableWidget;


// 主界面
class CalibrateWin : public CountFuncWin
{
    Q_OBJECT

public:
    CalibrateWin(QWidget* parent = 0);
    virtual ~CalibrateWin();

    // 吸样键按下
    virtual void onAbsorbKeyDown();

protected:
    // 界面字符串
    virtual void setWindowText();

    // 创建状态条
    virtual void createStatusBar();

    // 界面使能
    virtual void enableWindow(bool enable);

    // 切换到功能窗口
    virtual void switchToFuncWin(FuncWin* funcWin);

private slots:
    // 按钮点击
    void onBtnClearClicked();
    void onBtnSetupClicked();

    // 算法结束
    void onCountAlgFinished();
    // 计数结束
    void onCountFinished(bool result);

private:
    // 是否校准中
    bool isCalibrating() const;
    // 是否校准通过
    bool isCalibrateOk() const;
    // 是否校准设置
    bool isCalibrateSetted() const;
    // 是否校准结束
    bool isCalibrateFinished() const;

    // 保存校准结果
    bool saveCalibrateResult();

    // 显示校准设置信息
    void showCalibrateInfo(const QString& lotNo);
    // 显示校准结果信息
    void showCalibrateResult(const ParaList& targets, const QList<ParaList>& results);

private:
    Ui::CalibrateWin ui;

    // 计数服务
    Count* count;

    // 校准设置信息
    QString lotNo;
    ParaList targets;

    // 校准计数结果
    QList<ParaList> results;

    // 变异系数
    ParaList cvs;
    // 校准系数结果
    ParaList factors;

    // 校准表格
    CalibrateTableWidget* tableWidget;
};


#endif // _CALIBRATE_WIN_H_
