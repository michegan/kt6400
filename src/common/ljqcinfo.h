#ifndef _LJ_QC_INFO_H_
#define _LJ_QC_INFO_H_


#include <QDateTime>

#include "modes.h"
#include "libcommon.h"


// 样本信息
class COMMON_EXPORT LJQcInfo
{
public:
    LJQcInfo();
    LJQcInfo(const LJQcInfo& other);
    virtual ~LJQcInfo();

    // 是否设置
    bool isSetted() const;

    // 文件描述
    QString fileDesc() const;

    // 进样模式
    quint8 sampleMode() const;

    // 工作模式
    quint8 workMode() const;

    // 血样模式
    quint8 bloodMode() const;

    // 分析模式
    quint8 analysisMode() const;

    // 运算符重载
    LJQcInfo& operator=(const LJQcInfo& other);

public:
    // 文件描述
    static QString fileDesc(int fileNo);

public:
    // 文件号
    int fileNo;

    // 模式
    Modes modes;

    // 批号
    QString lotNo;

    // 有效期
    QDateTime expTime;

    // 样本编号
    QString sampleId;

    // 是否使用
    bool isUsed;
};


#endif // _LJ_QC_INFO_H_