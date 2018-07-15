#include <QtDebug>

#include "messagebox.h"
#include "departmenttable.h"
#include "departmenteditdialog.h"
#include "departmentsetupdialog.h"
#include "departmenttablewidget.h"


DepartmentSetupDialog::DepartmentSetupDialog(QWidget* parent, Qt::WFlags flags)
    : Dialog(parent), departmentTable(new DepartmentTable()), tableWidget(new DepartmentTableWidget(this))
{
    ui.setupUi(this);

    // �����б�
    this->tableWidget->setGeometry(20, 20, 420, 460);

    // �������п�����Ϣ
    this->onDepartmentTableDataChanged();

    // �����źŲ�
    connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(ui.pbEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    connect(this->departmentTable, SIGNAL(dataChanged()), this, SLOT(onDepartmentTableDataChanged()));
}

DepartmentSetupDialog::~DepartmentSetupDialog()
{

}

// �����ַ���
void DepartmentSetupDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.pbAdd, "IDS_ADD");
    this->setText(ui.pbEdit, "IDS_EDIT");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ���ݱ仯
void DepartmentSetupDialog::onDepartmentTableDataChanged()
{
    // ϵͳ���п���
    this->fids = this->departmentTable->departments();

    // ���������Ŀ��Ҳ���ʾ�ڿ��ұ����
    this->departments.clear();

    foreach (int fid, this->fids)
    {
        Department department;
        if (this->departmentTable->department(fid, department.deptId, department.deptName))
        {
            departments.append(department);
        }
    }

    // ˢ�¿����б�
    this->tableWidget->setDepartments(this->departments);
}

// ��ť���
void DepartmentSetupDialog::onBtnAddClicked()
{
    DepartmentEditDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        // �¿���
        Department department = dialog.getDepartment();

        // �������Ƿ��ظ�
        QList<int> fids = this->departmentTable->fids(department.deptName);
        if (0 < fids.length())
        {
            // �������ظ�����������
            MessageBox::warningIds(this, "IDS_USER_EXIST");
        }
        else
        {
            // ���浽���ݿ�
            int fid = 0;
            this->departmentTable->insertDepartment(fid, department.deptId, department.deptName);
        }
    }
}

void DepartmentSetupDialog::onBtnEditClicked()
{
    // ���Ա༭��ǰ����
    int row = this->tableWidget->current();
    if (0 <= row && row < this->fids.length())
    {
        DepartmentEditDialog dialog(this);

        dialog.setDepartment(this->departments[row]);
        if (QDialog::Accepted == dialog.exec())
        {
            // �¿���
            Department department = dialog.getDepartment();

            // �������Ƿ��ظ�
            QList<int> fids = this->departmentTable->fids(department.deptName);
            if (1 < fids.length())
            {
                // �������ظ�����������
                MessageBox::warningIds(this, "IDS_USER_EXIST");
            }
            else
            {
                this->departmentTable->updateDepartment(this->fids.at(row), department.deptId, department.deptName);
            }
        }
    }
}

void DepartmentSetupDialog::onBtnCancelClicked()
{
    this->reject();
}