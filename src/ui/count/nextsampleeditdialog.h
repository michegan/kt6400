#ifndef _NEXT_SAMPLE_EDIT_DIALOG_H_
#define _NEXT_SAMPLE_EDIT_DIALOG_H_


#include <QButtonGroup>

#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "sampleinfo.h"
#include "ui_nextsampleeditdialog.h"


// 下一样本编辑对话框
class NextSampleEditDialog : public Dialog
{
    Q_OBJECT

public:
    NextSampleEditDialog(QWidget* parent = 0);
    virtual ~NextSampleEditDialog();

    // 样本信息
    SampleInfo getSampleInfo();
    void setSampleInfo(const SampleInfo& sampleInfo);

protected:
    // 界面字符串
    virtual void setWindowText();

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 按钮组
    QButtonGroup* groupMode;
    QButtonGroup* groupGender;

    // 送检者
    QList<Doctor> senders;
    // 科室
    QList<Department> departments;

    // 年龄单位
    QStringList ageUnits;

    // 样本信息
    SampleInfo sampleInfo;

    // 界面
    Ui::NextSampleEditDialog ui;
};


#endif // _NEXT_SAMPLE_EDIT_DIALOG_H_