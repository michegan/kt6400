#ifndef _HAL_H_
#define _HAL_H_


// FPGA指令
enum FPGA_CMD
{
    // 设置增益（增益值）
    WBC_GAIN = 54, 
    RBC_GAIN = 55, 
    HGB_GAIN = 57, 

    // 开启HGB灯（开关）
    HGB_LED = 27, 

    // HGB数据采集（无）
    HGB_BK_COLLECT = 11, 
    HGB_REF_COLLECT = 10, 

    // WBC，RBC，PLT数据采集（开关）
    WBC_RBC_PLT_COLLECT_START = 12, 
    WBC_RBC_PLT_COLLECT_STOP = 5, 

    // 恒流源（开关）
    WBC_CONST = 28, 

    // WBC灼烧（开关）
    WBC_BURN = 29, 
    // RBC灼烧（开关）
    RBC_BURN = 30, 

    // 吸样键
    ABSORBKEY_STATE = 31, 

    // 测试速度
    TEST_SPEED = 37, 

    // 试剂余量
    SET_LH_REMAIN = 50,
    READ_LH_REMAIN = 51,

    SET_LH_VOLUME = 52,
    READ_LH_VOLUME = 53,
};


// MCU对象
enum MCU_OBJECT
{
    // 水平电机
    MOTOR_X = 0x04, 

    // 垂直电机
    MOTOR_Y = 0x0E, 
};


#endif // _HAL_H_
