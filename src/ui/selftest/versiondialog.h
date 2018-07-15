#ifndef _VERSION_DIALOG_H_
#define _VERSION_DIALOG_H_


#include "dialog.h"
#include "ui_versiondialog.h"


// 模式编辑对话框
class VersionDialog : public Dialog
{
    Q_OBJECT

public:
    VersionDialog(QWidget* parent = 0);
    virtual ~VersionDialog();

protected:
    // 界面字符串
    virtual void setWindowText();

private:
    // 加载版本信息
    void loadVersionInfo();

private:
    // 界面
    Ui::VersionDialog ui;
};


#endif // _VERSION_DIALOG_H_