#ifndef _SAMPLE_INFO_H_
#define _SAMPLE_INFO_H_


#include <QDateTime>
#include <QStringList>

#include "modes.h"
#include "libcommon.h"


// 样本信息
class COMMON_EXPORT SampleInfo
{
public:
    SampleInfo();
    SampleInfo(const SampleInfo& other);
    virtual ~SampleInfo();

    // 自动递增
    void autoInc();

    // 工作模式
    quint8 workMode() const;

    // 进样模式
    quint8 sampleMode() const;

    // 物种模式
    quint8 speciesMode() const;

    // 血样模式
    quint8 bloodMode() const;

    // 分析模式
    quint8 analysisMode() const;

    // 对应的参考组
    QString refRangeGroup() const;

    // 性别格式化
    QString genderIds() const;

    // 运算符重载
    SampleInfo& operator=(const SampleInfo& other);

public:
    // 样本编号
    QString sampleId;

    // 模式
    Modes modes;

    // 送检者
    QString sender;
    QDateTime sendTime;

    // 检验者
    QString tester;
    QDateTime testTime;

    // 审核者
    QString checker;
    QDateTime checkTime;

    // 病历号
    QString patientId;

    // 姓名
    QString name;

    // 性别
    int gender;
    
    // 年龄
    QString age;

    // 科室
    QString department;

    // 床号
    QString bedNo;

    // 备注
    QString comment;

    // 文件号
    int fileNo;
};


#endif // _SAMPLE_INFO_H_