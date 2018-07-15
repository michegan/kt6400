#ifndef _REF_RANGE_SETUP_DIALOG_H_
#define _REF_RANGE_SETUP_DIALOG_H_


#include "para.h"
#include "setupdialog.h"
#include "ui_refrangesetupdialog.h"


// 模式编辑对话框
class RefRangeSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    RefRangeSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~RefRangeSetupDialog();

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
    void onGroupComboBoxCurrentIndexChanged(int index);
    void onSpeciesComboBoxCurrentIndexChanged(int index);

private:
    // 关键字
    QStringList keys1;
    QStringList keys2;

    // 参考范围（修改后）
    ParaList lowLimits;
    ParaList highLimits;

    // 界面
    Ui::RefRangeSetupDialog ui;

    // 编辑框
    QMap<QString, DigitLineEdit*> lowEdits;
    QMap<QString, DigitLineEdit*> highEdits;
};


#endif // _REF_RANGE_SETUP_DIALOG_H_