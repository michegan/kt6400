#ifndef _NEXT_PET_EDIT_DIALOG_H_
#define _NEXT_PET_EDIT_DIALOG_H_


#include "dialog.h"
#include "sampleinfo.h"
#include "ui_nextpeteditdialog.h"


// ��һ�����༭�Ի���
class NextPetEditDialog : public Dialog
{
    Q_OBJECT

public:
    NextPetEditDialog(QWidget* parent = 0);
    virtual ~NextPetEditDialog();

    // ������Ϣ
    SampleInfo getSampleInfo();
    void setSampleInfo(const SampleInfo& sampleInfo);

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ������Ϣ
    SampleInfo sampleInfo;

    // ����
    Ui::NextPetEditDialog ui;
};


#endif // _NEXT_PET_EDIT_DIALOG_H_