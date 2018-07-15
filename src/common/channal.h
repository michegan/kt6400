#ifndef _CHANNAL_H_
#define _CHANNAL_H_


// 通道类型
enum CHANNAL_ID
{
    CHANNAL_WBC = 0x01, // WBC通道
    CHANNAL_RBC = 0x02, // RBC通道
    CHANNAL_PLT = 0x04, // PLT通道
    CHANNAL_HGB = 0x10, // HGB通道
    CHANNAL_ALL = 0xFF, // 所有通道
};


#endif // _CHANNAL_H_
