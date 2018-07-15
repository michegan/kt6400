#ifndef _NEXT_SAMPLE_EDIT_DIALOG_H_
#define _NEXT_SAMPLE_EDIT_DIALOG_H_


#include <QButtonGroup>

#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "sampleinfo.h"
#include "ui_nextsampleeditdialog.h"


// ��һ�����༭�Ի���
class NextSampleEditDialog : public Dialog
{
    Q_OBJECT

public:
    NextSampleEditDialog(QWidget* parent = 0);
    virtual ~NextSampleEditDialog();

    // ������Ϣ
    SampleInfo getSampleInfo();
    void setSampleInfo(const SampleInfo& sampleInfo);

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ��ť��
    QButtonGroup* groupMode;
    QButtonGroup* groupGender;

    // �ͼ���
    QList<Doctor> senders;
    // ����
    QList<Department> departments;

    // ���䵥λ
    QStringList ageUnits;

    // ������Ϣ
    SampleInfo sampleInfo;

    // ����
    Ui::NextSampleEditDialog ui;
};


#endif // _NEXT_SAMPLE_EDIT_DIALOG_H_