#ifndef _DOCTOR_EDIT_DIALOG_H_
#define _DOCTOR_EDIT_DIALOG_H_


#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "ui_doctoreditdialog.h"


// ҽ���༭�Ի���
class DoctorEditDialog : public Dialog
{
    Q_OBJECT

public:
    DoctorEditDialog(QWidget* parent = 0);
    virtual ~DoctorEditDialog();

    // ҽ����Ϣ
    Doctor getDoctor();
    void setDoctor(const Doctor& doctor);
    // �����б�
    void setDepartments(const QList<Department>& departments);

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ��ť���
    virtual void onBtnOkClicked();
    virtual void onBtnCancelClicked();

private:
    // ����
    Ui::DoctorEditDialog ui;
    // �����б�
    QList<Department> departments;
};


#endif // _DOCTOR_EDIT_DIALOG_H_