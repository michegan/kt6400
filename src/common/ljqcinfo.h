#ifndef _LJ_QC_INFO_H_
#define _LJ_QC_INFO_H_


#include <QDateTime>

#include "modes.h"
#include "libcommon.h"


// ������Ϣ
class COMMON_EXPORT LJQcInfo
{
public:
    LJQcInfo();
    LJQcInfo(const LJQcInfo& other);
    virtual ~LJQcInfo();

    // �Ƿ�����
    bool isSetted() const;

    // �ļ�����
    QString fileDesc() const;

    // ����ģʽ
    quint8 sampleMode() const;

    // ����ģʽ
    quint8 workMode() const;

    // Ѫ��ģʽ
    quint8 bloodMode() const;

    // ����ģʽ
    quint8 analysisMode() const;

    // ���������
    LJQcInfo& operator=(const LJQcInfo& other);

public:
    // �ļ�����
    static QString fileDesc(int fileNo);

public:
    // �ļ���
    int fileNo;

    // ģʽ
    Modes modes;

    // ����
    QString lotNo;

    // ��Ч��
    QDateTime expTime;

    // �������
    QString sampleId;

    // �Ƿ�ʹ��
    bool isUsed;
};


#endif // _LJ_QC_INFO_H_