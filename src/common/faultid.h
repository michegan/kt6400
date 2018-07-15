#ifndef _FAULT_ID_H_
#define _FAULT_ID_H_


// 故障ID
enum FaultID
{
    FAULT_WBC_CLOG = 0, // WBC堵孔
    FAULT_RBC_CLOG, // RBC堵孔
    FAULT_WBC_BUBBLE, // RBC气泡
    FAULT_HGB_BUBBLE, // HGB气泡
    FAULT_HGB_ERROR, // HGB故障

    FAULT_MOTOR_H, // 水平电机故障
    FAULT_MOTOR_V, // 垂直电机故障
    FAULT_SYRINGE_1, // 吸样泵电机故障
    FAULT_SYRINGE_2, // 负NO压泵电机故障

    FAULT_NO_LYSE, // 溶血剂空
    FAULT_NO_DILUENT, // 稀释液空
    FAULT_WASTE_FULL, // 废液满

    FAULT_BACKGROUND, // 本底异常

    FAULT_NO_PAPER, // 打印机缺纸
};


#endif // _FAULT_ID_H_