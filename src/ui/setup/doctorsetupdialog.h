#ifndef _DOCTOR_SETUP_DIALOG_H_
#define _DOCTOR_SETUP_DIALOG_H_


#include "doctor.h"
#include "dialog.h"
#include "department.h"
#include "ui_doctorsetupdialog.h"

class DoctorTable;
class DoctorTableWidget;


// ҽ�����öԻ���
class DoctorSetupDialog : public Dialog
{
    Q_OBJECT

public:
    DoctorSetupDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
    virtual ~DoctorSetupDialog();

protected:
    // �����ַ���
    virtual void setWindowText();

private slots:
    // ���ݱ仯
    void onDoctorTableDataChanged();

    // ��ť���
    virtual void onBtnAddClicked();
    virtual void onBtnEditClicked();
    virtual void onBtnDeleteClicked();
    virtual void onBtnCancelClicked();

private:
    // ҽ����Ϣ
    QList<int> fids;
    QList<Doctor> doctors;

    // ������Ϣ
    QList<Department> departments;

    // ҽ����
    DoctorTable* doctorTable;
    // ҽ���б�
    DoctorTableWidget* tableWidget;

    // ����
    Ui::DoctorSetupDialog ui;
};


#endif // _DOCTOR_SETUP_DIALOG_H_