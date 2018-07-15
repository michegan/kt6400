#include <QStringList>

#include "ljqcinfo.h"


LJQcInfo::LJQcInfo()
    : fileNo(1), modes(Modes()), lotNo(""), expTime(QDateTime()), sampleId(""), isUsed(false)
{

}

LJQcInfo::LJQcInfo(const LJQcInfo& other)
{
    // 文件号
    this->fileNo = other.fileNo;

    // 模式
    this->modes = other.modes;

    // 批号
    this->lotNo = other.lotNo;

    // 有效期
    this->expTime = other.expTime;

    // 样本编号
    this->sampleId = other.sampleId;

    // 是否使用
    this->isUsed = other.isUsed;
}

LJQcInfo::~LJQcInfo()
{

}

// 是否设置
bool LJQcInfo::isSetted() const
{
    // 必须设置批号和有效期信息
    return !(this->lotNo.isEmpty() || this->expTime.isNull());
}

// 文件描述（1 2 3 4 5 6 7 8 9->L1 L2 L3 M1 M2 M3 H1 H2 H3）
QString LJQcInfo::fileDesc() const
{
    return this->fileDesc(this->fileNo);
}

// 工作模式
quint8 LJQcInfo::workMode() const
{
    return this->modes.workMode;
}

// 进样模式
quint8 LJQcInfo::sampleMode() const
{
    return this->modes.sampleMode;
}

// 血样模式
quint8 LJQcInfo::bloodMode() const
{
    return this->modes.bloodMode;
}

// 分析模式
quint8 LJQcInfo::analysisMode() const
{
    return this->modes.analysisMode;
}

// 运算符重载
LJQcInfo& LJQcInfo::operator=(const LJQcInfo& other)
{
    // 文件号
    this->fileNo = other.fileNo;

    // 模式
    this->modes = other.modes;

    // 批号
    this->lotNo = other.lotNo;

    // 有效期
    this->expTime = other.expTime;

    // 样本编号
    this->sampleId = other.sampleId;

    // 是否使用
    this->isUsed = other.isUsed;

    return *this;
}

// 文件描述
QString LJQcInfo::fileDesc(int fileNo)
{
    QStringList levels;
    levels << "L" << "M" << "H";

    int index = (fileNo - 1) / levels.length();
    int offset = (fileNo - 1) % levels.length();

    return QString("%1%2").arg(levels.at(index)).arg(offset + 1);
}