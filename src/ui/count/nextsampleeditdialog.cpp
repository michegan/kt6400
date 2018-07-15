#include <QtDebug>

#include "age.h"
#include "define.h"
#include "gender.h"
#include "datetime.h"
#include "doctortable.h"
#include "departmenttable.h"
#include "nextsampleeditdialog.h"


NextSampleEditDialog::NextSampleEditDialog(QWidget* parent)
    : Dialog(parent), sampleInfo(SampleInfo())
{
    ui.setupUi(this);

    // �����ַ���
    this->setWindowText();

    this->groupMode = new QButtonGroup(this);
    this->groupMode->addButton(ui.rbWholeBlood);
    this->groupMode->addButton(ui.rbPeripheral);
    this->groupMode->addButton(ui.rbPrediluent);

    this->groupGender = new QButtonGroup(this);
    this->groupGender->addButton(ui.rbMale);
    this->groupGender->addButton(ui.rbFemale);

    // ���䵥λ
    this->ageUnits = Age::ageUnits();
    ui.cbAgeUnit->insertItems(0, this->ageUnits);

    // �ͼ���
    DoctorTable doctorTable;
    QList<int> fids = doctorTable.doctors();

    foreach (int fid, fids)
    {
        Doctor doctor;
        if (doctorTable.doctor(fid, doctor.doctorId, doctor.doctorName, doctor.deptId))
        {
            this->senders.append(doctor);
        }
    }

    QStringList senderNames;
    foreach (Doctor doctor, this->senders)
    {
        senderNames.append(doctor.doctorName);
    }
    ui.cbSender->addItems(senderNames);

    // ����
    DepartmentTable departmentTable;
    fids = departmentTable.departments();

    foreach (int fid, fids)
    {
        Department department;
        if (departmentTable.department(fid, department.deptId, department.deptName))
        {
            this->departments.append(department);
        }
    }

    QStringList departmentNames;
    foreach (Department department, this->departments)
    {
        departmentNames.append(department.deptName);
    }
    ui.cbDepartment->addItems(departmentNames);

    // ��󳤶�
    ui.leSampleId->setMaxLength(MAX_SID_LEN);
    ui.lePatientId->setMaxLength(MAX_PID_LEN);
    ui.leName->setMaxLength(MAX_NAME_LEN);
    ui.leAgeVal->setMaxLength(MAX_AGE_LEN);

    // �����źŲ�
    connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(onBtnOkClicked()));
    connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

NextSampleEditDialog::~NextSampleEditDialog()
{

}

// ������Ϣ
SampleInfo NextSampleEditDialog::getSampleInfo()
{
    return this->sampleInfo;
}

void NextSampleEditDialog::setSampleInfo(const SampleInfo& sampleInfo)
{
    // ������Ϣ
    this->sampleInfo = sampleInfo;

    // ������ʾ
    ui.leSampleId->setText(sampleInfo.sampleId);

    if (PREPROCESS_MODE_PREDILUENT == sampleInfo.modes.preprocessMode)
    {
        ui.rbPrediluent->setChecked(true);
    }
    else
    {
        ui.rbPeripheral->setChecked(BLOOD_MODE_PERIPHERAL == sampleInfo.modes.bloodMode);
        ui.rbWholeBlood->setChecked(BLOOD_MODE_PERIPHERAL != sampleInfo.modes.bloodMode);
    }

    ui.lePatientId->setText(sampleInfo.patientId);
    ui.leName->setText(sampleInfo.name);

    ui.rbMale->setChecked(GENDER_FEMALE != sampleInfo.gender);
    ui.rbFemale->setChecked(GENDER_FEMALE == sampleInfo.gender);

    if (sampleInfo.age.isEmpty())
    {
        ui.leAgeVal->setText("");
        ui.cbAgeUnit->setCurrentIndex(0);
    }
    else
    {
        QString ageUnit = sampleInfo.age.right(1);
        QString ageVal = sampleInfo.age.left(sampleInfo.age.length() - 1);

        ui.leAgeVal->setText(ageVal);
        ui.cbAgeUnit->setCurrentIndex(this->ageUnits.indexOf(ageUnit));
    }

    for (int i = 0; i < this->senders.length(); i++)
    {
        Doctor doctor = this->senders.at(i);
        if (doctor.doctorName == sampleInfo.sender)
        {
            ui.cbSender->setCurrentIndex(i);
        }
    }

    for (int i = 0; i < this->departments.length(); i++)
    {
        Department department = this->departments.at(i);
        if (department.deptName == sampleInfo.department)
        {
            ui.cbDepartment->setCurrentIndex(i);
        }
    }

    ui.teComment->setText(sampleInfo.comment);
}

// �����ַ���
void NextSampleEditDialog::setWindowText()
{
    // ���ദ��
    Dialog::setWindowText();

    // ���ദ��
    this->setText(ui.lbSampleId, "IDS_SAMPLE_ID");
    this->setText(ui.lbMode, "IDS_MODE");
    this->setText(ui.rbWholeBlood, "IDS_WHOLE_BLOOD");
    this->setText(ui.rbPeripheral, "IDS_PERIPHERAL");
    this->setText(ui.rbPrediluent, "IDS_PREDILUENT");
    this->setText(ui.lbPatientId, "IDS_PATIENT_ID");
    this->setText(ui.lbName, "IDS_NAME");
    this->setText(ui.lbGender, "IDS_GENDER");
    this->setText(ui.rbMale, "IDS_MALE");
    this->setText(ui.rbFemale, "IDS_FEMALE");
    this->setText(ui.lbAge, "IDS_AGE");
    this->setText(ui.lbDepartment, "IDS_DEPARTMENT");
    this->setText(ui.lbSender, "IDS_SENDER");
    this->setText(ui.lbComment, "IDS_COMMENT");
    this->setText(ui.pbOk, "IDS_OK");
    this->setText(ui.pbCancel, "IDS_CANCEL");
}

// ��ť���
void NextSampleEditDialog::onBtnOkClicked()
{
    // ��ȡ������Ϣ
    this->sampleInfo.sampleId = ui.leSampleId->text();

    if (ui.rbPrediluent->isChecked())
    {
        this->sampleInfo.modes.bloodMode = BLOOD_MODE_PERIPHERAL;
        this->sampleInfo.modes.preprocessMode = PREPROCESS_MODE_PREDILUENT;
    }
    else
    {
        this->sampleInfo.modes.preprocessMode = PREPROCESS_MODE_NONE;
        if (ui.rbPeripheral->isChecked())
        {
            this->sampleInfo.modes.bloodMode = BLOOD_MODE_PERIPHERAL;
        }
        else
        {
            this->sampleInfo.modes.bloodMode = BLOOD_MODE_WHOLE_BLOOD;
        }
    }

    this->sampleInfo.patientId = ui.lePatientId->text();
    this->sampleInfo.name = ui.leName->text();

    this->sampleInfo.gender = (ui.rbFemale->isChecked() ? GENDER_FEMALE : GENDER_MALE);
    this->sampleInfo.age = (ui.leAgeVal->text().isEmpty() ? "" : ui.leAgeVal->text() + ui.cbAgeUnit->currentText());

    int index = ui.cbSender->currentIndex();
    this->sampleInfo.sender = (0 <= index ? this->senders.at(index).doctorName : "");

    index = ui.cbDepartment->currentIndex();
    this->sampleInfo.department = (0 <= index ? this->departments.at(index).deptName : "");

    this->sampleInfo.comment = ui.teComment->toPlainText();

    // �رնԻ���
    this->accept();
}

void NextSampleEditDialog::onBtnCancelClicked()
{
    this->reject();
}