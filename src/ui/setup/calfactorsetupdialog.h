#ifndef _CAL_FACTOR_SETUP_DIALOG_H_
#define _CAL_FACTOR_SETUP_DIALOG_H_


#include <QMap>

#include "calfactor.h"
#include "setupdialog.h"
#include "ui_calfactorsetupdialog.h"


// 校准系数编辑对话框
class CalFactorSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    CalFactorSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~CalFactorSetupDialog();

protected:
    // 从界面获取设置信息
    virtual void getSetupInfoFromUI();

    // 设置信息有效性检测（有效返回0，无效返回对应错误码）
    virtual QString isSetupInfoValid();

    // 设置信息无效处理（提示信息）
    virtual QString onSetupInfoInvalidText(const QString& ret);
    virtual QWidget* onSetupInfoInvalidWidget(const QString& ret);

    // 设置信息有效处理（保存设置信息）
    virtual bool onSetupInfoValid();

private slots:
    // 按钮点击
    void onBtnPrintClicked();

private:
    // 关键字
    QString key1() const;

private:
    // 校准系数（修改后）
    QMap<QString, float> peripheralValues;
    QMap<QString, float> prediluentValues;
    QMap<QString, float> wholeBloodValues;

    // 界面
    Ui::CalFactorSetupDialog ui;

    // 界面控件
    QMap<QString, DigitLineEdit*> peripheralValueEdits;
    QMap<QString, DigitLineEdit*> prediluentValueEdits;
    QMap<QString, DigitLineEdit*> wholeBloodValueEdits;
};


#endif // _CAL_FACTOR_SETUP_DIALOG_H_