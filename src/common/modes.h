#ifndef _MODES_H_
#define _MODES_H_


#include <QList>
#include <QStringList>

#include <libcommon.h>


// ����ģʽ����ʲô�����½��еļ�����
// 4 Bits��֧��15�֣�
enum WORK_MODES
{
    WORK_MODE_NORMAL = 1, // ��������
    WORK_MODE_QC = 2, // �ʿؼ���
    WORK_MODE_CALIBRATE = 3, // У׼����
    WORK_MODE_AGING = 6, // �ϻ�����
    WORK_MODE_BACKGROUND = 7, // ���׼���
    WORK_MODE_GAIN = 10, // �������

    MAX_WORK_MODE = 15, // ����λ
};

// ����ģʽ������������ʽ��
// 3 Bits��֧��7�֣�
enum SAMPLE_MODES
{
    SAMPLE_MODE_OPEN = 1, // ���Ž���

    MAX_SAMPLE_MODE = 7, // ����λ
};

// ����ģʽ�����������������֣�
// 5 Bits��֧��31�֣�
enum SPECIES_MODES
{
    SPECIES_MODE_UNKNOWN = 1, // δ֪
    SPECIES_MODE_HUMAN = 2, // ��
    SPECIES_MODE_CAT = 3, // è
    SPECIES_MODE_DOG = 4, // ��
    SPECIES_MODE_MOUSE = 5, // ��
    SPECIES_MODE_RABBIT = 6, // ��

    MAX_SPECIES_MODE = 31, // ����λ
};

// Ѫ��ģʽ�������Ķ�����ʲô��
// 4 Bits��֧��15�֣�
enum BLOOD_MODES
{
    BLOOD_MODE_WHOLE_BLOOD = 1, // ����ȫѪ
    BLOOD_MODE_PERIPHERAL = 2, // ĩ��ȫѪ
    BLOOD_MODE_QC = 3, // �ʿ���
    BLOOD_MODE_CALIBRATE = 4, // У׼��
    BLOOD_MODE_BACKGROUND = 6, // ����

    MAX_BLOOD_MODE = 15, // ����λ
};

// ����ģʽ����Ҫ�����Щ������
// 8 Bits����֧��255�֣�
enum ANALYSIS_MODES
{
    ANALYSIS_MODE_CBC = 0x01, // CBCģʽ
};

// Ԥ����ʽ
// 2 Bits��֧��3�֣�
enum PREPROCESS_MODES
{
    PREPROCESS_MODE_NONE = 0, // ��Ԥ����
    PREPROCESS_MODE_PREDILUENT = 1, // ����Ԥϡ��

    MAX_PREPROCESS_MODE = 3, // ����λ
};

// Ԥ��ģʽ
// 6 Bits


// ģʽ
class COMMON_EXPORT Modes
{
public:
    Modes();
    virtual ~Modes();

    // ��ʽ��
    QString ids() const;

    // ����ģʽ��ʽ��
    QString specimodeIds() const;
    QString speciesImage() const;

public:
    // ����ģʽ
    quint8 workMode;
    // ����ģʽ
    quint8 sampleMode;
    // ����ģʽ
    quint8 speciesMode;
    // Ѫ��ģʽ
    quint8 bloodMode;
    // ����ģʽ
    quint8 analysisMode;
    // Ԥ����ģʽ
    quint8 preprocessMode;
};


#endif // _MODES_H_