#ifndef _HIST_INFO_H_
#define _HIST_INFO_H_


#include "libcommon.h"


// 分类线
const int Max_Hist_LineLen = 8;
const int Max_Hist_DataLen = 512;


// 直方图信息
class COMMON_EXPORT HistInfo 
{
public:
    HistInfo();
    HistInfo(const HistInfo& other);
    virtual ~HistInfo();

    // 初始化
    void clear();

    // 输出
    void output();

    // 运算符重载
    HistInfo& operator=(const HistInfo& other);

public:
    // 分类线
    int lineLen;
    int lines[Max_Hist_LineLen];

    // 直方图数据
    int dataLen;
    int datas[Max_Hist_DataLen];
};


class COMMON_EXPORT WbcHistInfo : public HistInfo
{
public:
    WbcHistInfo();
    virtual ~WbcHistInfo();
};


class COMMON_EXPORT RbcHistInfo : public HistInfo
{
public:
    RbcHistInfo();
    virtual ~RbcHistInfo();
};


class COMMON_EXPORT PltHistInfo : public HistInfo
{
public:
    PltHistInfo();
    virtual ~PltHistInfo();
};


#endif // _HIST_INFO_H_