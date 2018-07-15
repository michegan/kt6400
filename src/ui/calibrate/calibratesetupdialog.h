#ifndef _CALIBRATE_SETUP_DIALOG_H_
#define _CALIBRATE_SETUP_DIALOG_H_


#include <QMap>

#include "para.h"
#include "setupdialog.h"
#include "ui_calibratesetupdialog.h"


// 校准设置对话框
class CalibrateSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    CalibrateSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~CalibrateSetupDialog();

    // 校准信息（批号）
    QString lotNo() const;
    void setLotNo(const QString& lotNo);

    // 校准信息（靶值，含所有校准参数，通过FLAG区分）
    // PARA_IGNORE_FLAG：不校准此参数；PARA_NORMAL_FLAG：校准此参数；
    ParaList targets() const;
    void setTargets(const ParaList& targets);

protected:
    // 界面字符串
    virtual void setWindowText();

    // 从界面获取设置信息
    virtual void getSetupInfoFromUI();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid();

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid();

private:
    // 校准信息（修改后）
    QString slotNo;
    ParaList stargets;

    // 界面
    Ui::CalibrateSetupDialog ui;

    // 界面控件
    QMap<QString, DigitLineEdit*> valueEdits;
};


#endif // _CALIBRATE_SETUP_DIALOG_H_