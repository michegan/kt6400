#ifndef _LJ_QC_SETUP_WIN_
#define _LJ_QC_SETUP_WIN_


#include "para.h"
#include "ljqcinfo.h"
#include "setupfuncwin.h"
#include "ui_ljqcsetupwin.h"

class LJQcFileTable;


// LJ质控设置界面
class LJQcSetupWin : public SetupFuncWin
{
    Q_OBJECT

public:
    LJQcSetupWin(QWidget* parent = 0);
    virtual ~LJQcSetupWin();

protected:
    // 创建状态条
    virtual void createStatusBar();

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI();

    // 设置信息是否变化
    virtual bool isSetupInfoChanged();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid();

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid();

private slots:
    // 按钮点击
    void onBtnBackClicked();

private:
    // 文件号
    int fileNo;

    // 质控信息
    LJQcInfo ljQcInfoPre;
    LJQcInfo ljQcInfoPost;

    // 质控上下限
    ParaList lowLimitsPre;
    ParaList highLimitsPre;

    ParaList lowLimitsPost;
    ParaList highLimitsPost;

    // 底部状态栏
    QLabel* lbFileNo;
    QLabel* leFileNo;

    Ui::LJQcSetupWin ui;

    // 文件表
    LJQcFileTable* fileTable;

    // 编辑框
    QMap<QString, DigitLineEdit*> lowEdits;
    QMap<QString, DigitLineEdit*> highEdits;
};


#endif // _LJ_QC_SETUP_WIN_
