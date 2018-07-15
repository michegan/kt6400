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
    // 样本编号
    this->sampleId = other.sampleId;

    // 模式
    this->modes = other.modes;

    // 送检者
    this->sender = other.sender;
    this->sendTime = other.sendTime;

    // 检验者
    this->tester = other.tester;
    this->testTime = other.testTime;

    // 审核者
    this->checker = other.checker;
    this->checkTime = other.checkTime;

    // 病历号
    this->patientId = other.patientId;

    // 姓名
    this->name = other.name;

    // 性别
    this->gender = other.gender;

    // 年龄
    this->age = other.age;

    // 科室
    this->department = other.department;

    // 床号
    this->bedNo = other.bedNo;

    // 备注
    this->comment = other.comment;

    // 文件号
    this->fileNo = other.fileNo;
}

SampleInfo::~SampleInfo()
{

}

// 自动递增
void SampleInfo::autoInc()
{
    // 大部分信息都清空
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

    // 模式保持上一样本模式


    // 样本编号自动递增
    this->sampleId = SampleId::autoInc(this->sampleId);

    // 模式保持原样
    

    // 送检，检验，审核信息清空
   
    // 文件号
    this->fileNo = 0;
}

// 工作模式
quint8 SampleInfo::workMode() const
{
    return this->modes.workMode;
}

// 进样模式
quint8 SampleInfo::sampleMode() const
{
    return this->modes.sampleMode;
}

// 物种模式
quint8 SampleInfo::speciesMode() const
{
    return this->modes.speciesMode;
}

// 血样模式
quint8 SampleInfo::bloodMode() const
{
    return this->modes.bloodMode;
}

// 分析模式
quint8 SampleInfo::analysisMode() const
{
    return this->modes.analysisMode;
}

// 对应的参考组
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
                    // 13岁以上是成人，成男或者成女
                    return ((GENDER_FEMALE == this->gender) ? "IDS_ADULT_FEMALE" : "IDS_ADULT_MALE");
                }
                else
                {
                    // 13岁以下，儿童
                    return "IDS_CHILD";
                }
            }
            else if (Age::AgeUnitMonth == age.ageUnit)
            {
                // 只能是儿童
                return "IDS_CHILD";
            }
            else
            {
                // 28天以上是儿童，28天以下是新生儿
                return ((28 < age.ageVal) ? "IDS_CHILD" : "IDS_INFANT");
            }
        }
    }
    else
    {
        return "IDS_COMMON";
    }
}

// 性别格式化
QString SampleInfo::genderIds() const
{
    return ((GENDER_FEMALE == this->gender) ? "IDS_FEMALE" : "IDS_MALE");
}

// 运算符重载
SampleInfo& SampleInfo::operator=(const SampleInfo& other)
{
    // 样本编号
    this->sampleId = other.sampleId;

    // 模式
    this->modes = other.modes;

    // 送检者
    this->sender = other.sender;
    this->sendTime = other.sendTime;

    // 检验者
    this->tester = other.tester;
    this->testTime = other.testTime;

    // 审核者
    this->checker = other.checker;
    this->checkTime = other.checkTime;

    // 病历号
    this->patientId = other.patientId;

    // 姓名
    this->name = other.name;

    // 性别
    this->gender = other.gender;

    // 年龄
    this->age = other.age;

    // 科室
    this->department = other.department;

    // 床号
    this->bedNo = other.bedNo;

    // 备注
    this->comment = other.comment;

    // 文件号
    this->fileNo = other.fileNo;

    return *this;
}