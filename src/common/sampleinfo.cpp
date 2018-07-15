#include <QMap>

#include "age.h"
#include "gender.h"
#include "sampleid.h"
#include "sampleinfo.h"


SampleInfo::SampleInfo()
    : sampleId(""), modes(Modes()), sender(""), sendTime(QDateTime()), tester(""), testTime(QDateTime()), 
      checker(""), checkTime(QDateTime()), patientId(""), name(""), gender(GENDER_NULL), age(""), 
      department(""), bedNo(""), comment(""), fileNo(0)
{

}

SampleInfo::SampleInfo(const SampleInfo& other)
{
    // �������
    this->sampleId = other.sampleId;

    // ģʽ
    this->modes = other.modes;

    // �ͼ���
    this->sender = other.sender;
    this->sendTime = other.sendTime;

    // ������
    this->tester = other.tester;
    this->testTime = other.testTime;

    // �����
    this->checker = other.checker;
    this->checkTime = other.checkTime;

    // ������
    this->patientId = other.patientId;

    // ����
    this->name = other.name;

    // �Ա�
    this->gender = other.gender;

    // ����
    this->age = other.age;

    // ����
    this->department = other.department;

    // ����
    this->bedNo = other.bedNo;

    // ��ע
    this->comment = other.comment;

    // �ļ���
    this->fileNo = other.fileNo;
}

SampleInfo::~SampleInfo()
{

}

// �Զ�����
void SampleInfo::autoInc()
{
    // �󲿷���Ϣ�����
    this->sender.clear();
    this->sendTime = QDateTime();

    this->tester.clear();
    this->testTime = QDateTime();

    this->checker.clear();
    this->checkTime = QDateTime();

    this->patientId.clear();
    this->name.clear();

    this->gender = GENDER_NULL;
    this->age.clear();

    this->department.clear();
    this->bedNo.clear();
    this->comment.clear();

    // ģʽ������һ����ģʽ


    // ��������Զ�����
    this->sampleId = SampleId::autoInc(this->sampleId);

    // ģʽ����ԭ��
    

    // �ͼ죬���飬�����Ϣ���
   
    // �ļ���
    this->fileNo = 0;
}

// ����ģʽ
quint8 SampleInfo::workMode() const
{
    return this->modes.workMode;
}

// ����ģʽ
quint8 SampleInfo::sampleMode() const
{
    return this->modes.sampleMode;
}

// ����ģʽ
quint8 SampleInfo::speciesMode() const
{
    return this->modes.speciesMode;
}

// Ѫ��ģʽ
quint8 SampleInfo::bloodMode() const
{
    return this->modes.bloodMode;
}

// ����ģʽ
quint8 SampleInfo::analysisMode() const
{
    return this->modes.analysisMode;
}

// ��Ӧ�Ĳο���
QString SampleInfo::refRangeGroup() const
{
    int speciesMode = this->speciesMode();

    if (SPECIES_MODE_HUMAN == speciesMode)
    {
        Age age;
        age.fromString(this->age);

        if (age.ageVal < 0)
        {
            return "IDS_COMMON";
        }
        else
        {
            if (Age::AgeUnitYear == age.ageUnit)
            {
                if (13 <= age.ageVal)
                {
                    // 13�������ǳ��ˣ����л��߳�Ů
                    return ((GENDER_FEMALE == this->gender) ? "IDS_ADULT_FEMALE" : "IDS_ADULT_MALE");
                }
                else
                {
                    // 13�����£���ͯ
                    return "IDS_CHILD";
                }
            }
            else if (Age::AgeUnitMonth == age.ageUnit)
            {
                // ֻ���Ƕ�ͯ
                return "IDS_CHILD";
            }
            else
            {
                // 28�������Ƕ�ͯ��28��������������
                return ((28 < age.ageVal) ? "IDS_CHILD" : "IDS_INFANT");
            }
        }
    }
    else
    {
        return "IDS_COMMON";
    }
}

// �Ա��ʽ��
QString SampleInfo::genderIds() const
{
    return ((GENDER_FEMALE == this->gender) ? "IDS_FEMALE" : "IDS_MALE");
}

// ���������
SampleInfo& SampleInfo::operator=(const SampleInfo& other)
{
    // �������
    this->sampleId = other.sampleId;

    // ģʽ
    this->modes = other.modes;

    // �ͼ���
    this->sender = other.sender;
    this->sendTime = other.sendTime;

    // ������
    this->tester = other.tester;
    this->testTime = other.testTime;

    // �����
    this->checker = other.checker;
    this->checkTime = other.checkTime;

    // ������
    this->patientId = other.patientId;

    // ����
    this->name = other.name;

    // �Ա�
    this->gender = other.gender;

    // ����
    this->age = other.age;

    // ����
    this->department = other.department;

    // ����
    this->bedNo = other.bedNo;

    // ��ע
    this->comment = other.comment;

    // �ļ���
    this->fileNo = other.fileNo;

    return *this;
}