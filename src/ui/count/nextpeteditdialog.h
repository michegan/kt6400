#ifndef _NEXT_PET_EDIT_DIALOG_H_
#define _NEXT_PET_EDIT_DIALOG_H_


#include "dialog.h"
#include "sampleinfo.h"
#include "ui_nextpeteditdialog.h"


// 下一样本编辑对话框
class NextPetEditDialog : public Dialog
{
    Q_OBJECT

public:
    NextPetEditDialog(QWidget* parent = 0);
    virtual ~NextPetEditDialog();

    // 样本信息
    SampleInfo getSampleInfo();
    void setSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // 按钮点击
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // 样本信息
    SampleInfo sampleInfo;

    // 界面
    Ui::NextPetEditDialog ui;
};


#endif // _NEXT_PET_EDIT_DIALOG_H_