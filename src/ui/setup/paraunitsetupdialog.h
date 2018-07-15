#ifndef _PARA_UNIT_SETUP_DIALOG_H_
#define _PARA_UNIT_SETUP_DIALOG_H_


#include "unitwidget.h"
#include "setupdialog.h"
#include "ui_paraunitsetupdialog.h"


// 模式编辑对话框
class ParaUnitSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    ParaUnitSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~ParaUnitSetupDialog();

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
    // 下拉框当前选项变化
    void onComboBoxCurrentIndexChanged (const QString& text);

private:
    // 单位制（更改前）
    QString unit1;
    // 单位制（更改后）
    QString unit2;

    // 单位控件
    UnitWidget* wbcUnitWidget;
    UnitWidget* rbcUnitWidget;
    UnitWidget* pltUnitWidget;

    // 界面
    Ui::ParaUnitSetupDialog ui;
};


#endif // _PARA_UNIT_SETUP_DIALOG_H_