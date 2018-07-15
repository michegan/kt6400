#ifndef _FAULT_ID_H_
#define _FAULT_ID_H_


// ����ID
enum FaultID
{
    FAULT_WBC_CLOG = 0, // WBC�¿�
    FAULT_RBC_CLOG, // RBC�¿�
    FAULT_WBC_BUBBLE, // RBC����
    FAULT_HGB_BUBBLE, // HGB����
    FAULT_HGB_ERROR, // HGB����

    FAULT_MOTOR_H, // ˮƽ�������
    FAULT_MOTOR_V, // ��ֱ�������
    FAULT_SYRINGE_1, // �����õ������
    FAULT_SYRINGE_2, // ��NOѹ�õ������

    FAULT_NO_LYSE, // ��Ѫ����
    FAULT_NO_DILUENT, // ϡ��Һ��
    FAULT_WASTE_FULL, // ��Һ��

    FAULT_BACKGROUND, // �����쳣

    FAULT_NO_PAPER, // ��ӡ��ȱֽ
};


#endif // _FAULT_ID_H_