#ifndef _HIST_INFO_H_
#define _HIST_INFO_H_


#include "libcommon.h"


// ������
const int Max_Hist_LineLen = 8;
const int Max_Hist_DataLen = 512;


// ֱ��ͼ��Ϣ
class COMMON_EXPORT HistInfo 
{
public:
    HistInfo();
    HistInfo(const HistInfo& other);
    virtual ~HistInfo();

    // ��ʼ��
    void clear();

    // ���
    void output();

    // ���������
    HistInfo& operator=(const HistInfo& other);

public:
    // ������
    int lineLen;
    int lines[Max_Hist_LineLen];

    // ֱ��ͼ����
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