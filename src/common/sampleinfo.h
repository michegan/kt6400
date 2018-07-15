#ifndef _SAMPLE_INFO_H_
#define _SAMPLE_INFO_H_


#include <QDateTime>
#include <QStringList>

#include "modes.h"
#include "libcommon.h"


// ������Ϣ
class COMMON_EXPORT SampleInfo
{
public:
    SampleInfo();
    SampleInfo(const SampleInfo& other);
    virtual ~SampleInfo();

    // �Զ�����
    void autoInc();

    // ����ģʽ
    quint8 workMode() const;

    // ����ģʽ
    quint8 sampleMode() const;

    // ����ģʽ
    quint8 speciesMode() const;

    // Ѫ��ģʽ
    quint8 bloodMode() const;

    // ����ģʽ
    quint8 analysisMode() const;

    // ��Ӧ�Ĳο���
    QString refRangeGroup() const;

    // �Ա��ʽ��
    QString genderIds() const;

    // ���������
    SampleInfo& operator=(const SampleInfo& other);

public:
    // �������
    QString sampleId;

    // ģʽ
    Modes modes;

    // �ͼ���
    QString sender;
    QDateTime sendTime;

    // ������
    QString tester;
    QDateTime testTime;

    // �����
    QString checker;
    QDateTime checkTime;

    // ������
    QString patientId;

    // ����
    QString name;

    // �Ա�
    int gender;
    
    // ����
    QString age;

    // ����
    QString department;

    // ����
    QString bedNo;

    // ��ע
    QString comment;

    // �ļ���
    int fileNo;
};


#endif // _SAMPLE_INFO_H_