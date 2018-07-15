#include <QtDebug>

#include "messagebox.h"
#include "doctortable.h"
#include "departmenttable.h"
#include "doctoreditdialog.h"
#include "doctorsetupdialog.h"
#include "doctortablewidget.h"


DoctorSetupDialog::DoctorSetupDialog(QWidget* parent, Qt::WFlags flags)
    : Dialog(parent), doctorTable(new DoctorTable()), tableWidget(new DoctorTableWidget(this))
{
    ui.setupUi(this);

    // �����б�
    DepartmentTable departmentTable;
    QList<int> fids = departmentTable.departments();

    // ���������Ŀ��Ҳ���ʾ�ڿ��ұ����
    foreach (int fid, fids)
    {
        Department department;
        if (departmentTable.department(fid, department.deptId, department.deptName))
        {
            this->departments.append(department);
        }
    }

    // ҽ���б�
    this->tableWidget->setGeometry(20, 20, 420, 460);
    this->tableWidget->setDepartments(this->departments);

    // ��������ҽ����Ϣ
    this->onDoctorTableDataChanged();

    // �����źŲ�
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->doctorTable, SIGNAL(dataChanged()), this, SLOT(onDoctorTableDataChanged()));
}

DoctorSetupDialog::~DoctorSetupDialog()
{

}

// �����ַ���
void DoctorSetupDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbDelete, "IDS_DELETE");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ���ݱ仯
void DoctorSetupDialog::onDoctorTableDataChanged()                        
{
    // ϵͳ����ҽ��
    this->fids = this->doctorTable->doctors();

    // ����������ҽ������ʾ��ҽ�������
    this->doctors.clear();

    foreach (int fid, this->fids)
    {
        Doctor doctor;
        if (this->doctorTable->doctor(fid, doctor.doctorId, doctor.doctorName, doctor.deptId))
        {
            doctors.append(doctor);
        }
    }

    // ˢ��ҽ���б�
    this->tableWidget->setDoctors(this->doctors);
}

// ��ť���
void DoctorSetupDialog::onBtnAddClicked()
{
    DoctorEditDialog dialog(this);

    dialog.setDepartments(this->departments);

    if (QDialog::Accepted == dialog.exec())
    {
        // ��ҽ��
        Doctor doctor = dialog.getDoctor();

        // ҽ�����Ƿ��ظ�
        QList<int> fids = this->doctorTable->fids(doctor.doctorName);
        if (0 < fids.length())
        {
            // ҽ�����ظ�����������
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // ���浽���ݿ�
            int fid = 0;
            this->doctorTable->insertDoctor(fid, doctor.doctorId, doctor.doctorName, doctor.deptId);
        }
    }
}

void DoctorSetupDialog::onBtnEditClicked()
{
    // ���Ա༭��ǰҽ��
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        DoctorEditDialog dialog(this);

        dialog.setDepartments(this->departments);
        dialog.setDoctor(this->doctors[row]);

        if (QDialog::Accepted == dialog.exec())
        {
            // ��ҽ��
            Doctor doctor = dialog.getDoctor();

            // ҽ�����Ƿ��ظ�
            QList<int> fids = this->doctorTable->fids(doctor.doctorName);
            if (1 < fids.length())
            {
                // ҽ�����ظ�����������
                MessageBox::warningIds(this, "IDS_USER_EXIST");
            }
            else
            {
                this->doctorTable->updateDoctor(this->fids.at(row), doctor.doctorId, doctor.doctorName, doctor.deptId);
            }
        }
    }
}

void DoctorSetupDialog::onBtnDeleteClicked()
{
    // ����ɾ����ǰҽ��
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        this->doctorTable->deleteDoctor(this->fids.at(row));
    }
}

void DoctorSetupDialog::onBtnCancelClicked()
{
    this->reject();
}