#ifndef _ENUM_H_
#define _ENUM_H_


// 返回值
enum EXIT_RET
{
    EXIT_OK = 0, // 正常启动

    EXIT_BUSY_LIMITED, // 系统忙限制
    EXIT_FAULT_LIMITED, // 故障限制

    EXIT_FAIL, // 其他原因限制
};

// 通道类型
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
