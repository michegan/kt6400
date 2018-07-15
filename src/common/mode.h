#ifndef _MODE_H_
#define _MODE_H_


#include <QList>
#include <QString>

#include <libcommon.h>


// ����ģʽ
enum SAMPLE_MODE
{
    OPEN_MODE = 0x01, // ���Ž���
    AUTO_MODE = 0x02, // �Զ�����
    CLOSE_MODE = 0x04, // ��ս���
};

// ����ģʽ
enum WORK_MODE
{
    NORMAL_MODE = 0, // ��������
    QC_MODE, // �ʿؼ���
    USER_CALIBRATE_MODE, // У׼�������û���
    FACTORY_CALIBRATE_MODE, // У׼���������ң�
    REPEAT_QC_MODE, // �ظ��Լ������ʿأ�
    REPEAT_BLOOD_MODE, // �ظ��Լ�����Ѫ����
    AGING_MODE, // �ϻ�����
    SYS_BACKGROUND_MODE, // ���׼�����ϵͳ��
    USER_BACKGROUND_MODE, // ���׼������û���
    STANDARD_MODE, // ����ģʽ
    GAIN_MODE, // �������
    CARRYOVER_QC_MODE, // Я����Ⱦ�������ʿأ�
    CARRYOVER_BLOOD_MODE, // Я����Ⱦ������Ѫ����
    CALIBRATE_CONFIRM_MODE, // У׼ȷ�ϣ��ʿأ�
    CAL_SCALING_MODE, // CRP�궨

    WORK_MODE_RESERVE_1, // ����
    WORK_MODE_RESERVE_2, // ����
    WORK_MODE_RESERVE_3, // ����
    WORK_MODE_RESERVE_4, // ����
    WORK_MODE_RESERVE_5, // ����
    WORK_MODE_RESERVE_6, // ����
    WORK_MODE_RESERVE_7, // ����
    WORK_MODE_RESERVE_8, // ����
    WORK_MODE_RESERVE_9, // ����
    WORK_MODE_RESERVE_10, // ����
};

// Ѫ��ģʽ
enum BLOOD_MODE
{
    WHOLE_BLOOD_MODE = 0x01, // ȫѪģʽ
    PREDILUENT_MODE = 0x02, // Ԥϡ��ģʽ
    PERIPHERAL_MODE = 0x04, // ĩ��Ѫģʽ
};

// ����ģʽ
enum ANALYSIS_MODE
{
    CBC_MODE = 0x01, // CBCģʽ
    DIFF_MODE =0x02, // DIFFģʽ
    CRP_MODE = 0x04, // CRP ģʽ

    CBC_DIFF_MODE = (CBC_MODE | DIFF_MODE), // CBC-DIFFģʽ
    CBC_CRP_MODE = (CBC_MODE | CRP_MODE), // CBC_CRPģʽ
    CBC_DIFF_CRP_MODE = (CBC_DIFF_MODE | CRP_MODE), // CBC_DIFF_CRPģʽ
};


// ģʽ
namespace Mode
{
    // �Ƿ����CBCģʽ
    COMMON_EXPORT bool hasCbcMode(int am);

    // �Ƿ����DIFFģʽ
    COMMON_EXPORT bool hasDiffMode(int am);

    // �Ƿ����CRPģʽ
    COMMON_EXPORT bool hasCrpMode(int am);
};


#endif // _MODE_H_