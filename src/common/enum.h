#ifndef _ENUM_H_
#define _ENUM_H_


// ����ֵ
enum EXIT_RET
{
    EXIT_OK = 0, // ��������

    EXIT_BUSY_LIMITED, // ϵͳæ����
    EXIT_FAULT_LIMITED, // ��������

    EXIT_FAIL, // ����ԭ������
};

// ͨ������
enum ChannalType
{
    CHANNAL_TYPE_MIN = 0x00,
    CHANNAL_TYPE_WBC = CHANNAL_TYPE_MIN,
    CHANNAL_TYPE_RBC,
    CHANNAL_TYPE_DIFF,
    CHANNAL_TYPE_PLT,
    CHANNAL_TYPE_HGB,
    CHANNAL_TYPE_MAX = 0x10,
};

#endif // _ENUM_H_
