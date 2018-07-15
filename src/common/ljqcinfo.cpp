#include <QStringList>

#include "ljqcinfo.h"


LJQcInfo::LJQcInfo()
    : fileNo(1), modes(Modes()), lotNo(""), expTime(QDateTime()), sampleId(""), isUsed(false)
{

}

LJQcInfo::LJQcInfo(const LJQcInfo& other)
{
    // �ļ���
    this->fileNo = other.fileNo;

    // ģʽ
    this->modes = other.modes;

    // ����
    this->lotNo = other.lotNo;

    // ��Ч��
    this->expTime = other.expTime;

    // �������
    this->sampleId = other.sampleId;

    // �Ƿ�ʹ��
    this->isUsed = other.isUsed;
}

LJQcInfo::~LJQcInfo()
{

}

// �Ƿ�����
bool LJQcInfo::isSetted() const
{
    // �����������ź���Ч����Ϣ
    return !(this->lotNo.isEmpty() || this->expTime.isNull());
}

// �ļ�������1 2 3 4 5 6 7 8 9->L1 L2 L3 M1 M2 M3 H1 H2 H3��
QString LJQcInfo::fileDesc() const
{
    return this->fileDesc(this->fileNo);
}

// ����ģʽ
quint8 LJQcInfo::workMode() const
{
    return this->modes.workMode;
}

// ����ģʽ
quint8 LJQcInfo::sampleMode() const
{
    return this->modes.sampleMode;
}

// Ѫ��ģʽ
quint8 LJQcInfo::bloodMode() const
{
    return this->modes.bloodMode;
}

// ����ģʽ
quint8 LJQcInfo::analysisMode() const
{
    return this->modes.analysisMode;
}

// ���������
LJQcInfo& LJQcInfo::operator=(const LJQcInfo& other)
{
    // �ļ���
    this->fileNo = other.fileNo;

    // ģʽ
    this->modes = other.modes;

    // ����
    this->lotNo = other.lotNo;

    // ��Ч��
    this->expTime = other.expTime;

    // �������
    this->sampleId = other.sampleId;

    // �Ƿ�ʹ��
    this->isUsed = other.isUsed;

    return *this;
}

// �ļ�����
QString LJQcInfo::fileDesc(int fileNo)
{
    QStringList levels;
    levels << "L" << "M" << "H";

    int index = (fileNo - 1) / levels.length();
    int offset = (fileNo - 1) % levels.length();

    return QString("%1%2").arg(levels.at(index)).arg(offset + 1);
}