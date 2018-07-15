#ifndef _COUNT_FUNC_WIN_H_
#define _COUNT_FUNC_WIN_H_


#include "funcwin.h"
#include "sampleinfo.h"

class NextSampleTable;


// 支持计数的功能界面
class CountFuncWin : public FuncWin
{
    Q_OBJECT

public:
    CountFuncWin(QWidget* parent = 0);
    virtual ~CountFuncWin();

    // 下一样本信息
    SampleInfo getNextSampleInfo() const;
    void setNextSampleInfo(const SampleInfo& sampleInfo);

protected:
    // 创建状态条
    virtual void createStatusBar();

    // 界面使能
    virtual void enableWindow(bool enable);

    // 显示下一样本信息
    virtual void showNextSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // 按钮点击
    void onBtnModeClicked();
    void onBtnSpeciesClcked();

private:
    // 底部状态栏
    QPushButton* pbNextSpecies;
    QPushButton* pbNextSampleMode;

    // 下一样本信息
    SampleInfo* nextSampleInfo;
    // 下一样本数据表
    NextSampleTable* nextSampleTable;
};


#endif // _COUNT_FUNC_WIN_H_
