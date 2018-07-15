#ifndef _MACHINE_SETUP_DIALOG_H_
#define _MACHINE_SETUP_DIALOG_H_


#include "setupdialog.h"
#include "ui_machinesetupdialog.h"


// 仪器设置对话框
class MachineSetupDialog : public SetupDialog
{
    Q_OBJECT

public:
    MachineSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~MachineSetupDialog();

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

private:
    // 序列号（更改前）
    QString sn1;
    // 序列号（更改后）
    QString sn2;

    // 宠物版（更改前）
    int forPets1;
    // 宠物版（更改后）
    int forPets2;

    // 机型（更改前）
    QString machine1;
    // 机型（更改后）
    QString machine2;

    // 语言（更改前）
    QString language1;
    // 语言（更改后）
    QString language2;

    // 测试速度（更改前）
    QString testSpeed1;
    // 测试速度（更改后）
    QString testSpeed2;

    // 稀释比（更改前）
    QString diluent1;
    // 稀释比（更改后）
    QString diluent2;

    // 溶血剂耗量（更改前）
    QString lyse1;
    // 溶血剂耗量（更改后）
    QString lyse2;

    // 界面
    Ui::MachineSetupDialog ui;
};


#endif // _MACHINE_SETUP_DIALOG_H_