#ifndef _HAL_H_
#define _HAL_H_


// FPGAָ��
enum FPGA_CMD
{
    // �������棨����ֵ��
    WBC_GAIN = 54, 
    RBC_GAIN = 55, 
    HGB_GAIN = 57, 

    // ����HGB�ƣ����أ�
    HGB_LED = 27, 

    // HGB���ݲɼ����ޣ�
    HGB_BK_COLLECT = 11, 
    HGB_REF_COLLECT = 10, 

    // WBC��RBC��PLT���ݲɼ������أ�
    WBC_RBC_PLT_COLLECT_START = 12, 
    WBC_RBC_PLT_COLLECT_STOP = 5, 

    // ����Դ�����أ�
    WBC_CONST = 28, 

    // WBC���գ����أ�
    WBC_BURN = 29, 
    // RBC���գ����أ�
    RBC_BURN = 30, 

    // ������
    ABSORBKEY_STATE = 31, 

    // �����ٶ�
    TEST_SPEED = 37, 

    // �Լ�����
    SET_LH_REMAIN = 50,
    READ_LH_REMAIN = 51,

    SET_LH_VOLUME = 52,
    READ_LH_VOLUME = 53,
};


// MCU����
enum MCU_OBJECT
{
    // ˮƽ���
    MOTOR_X = 0x04, 

    // ��ֱ���
    MOTOR_Y = 0x0E, 
};


#endif // _HAL_H_
