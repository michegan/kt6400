#ifndef _FLAG_H_
#define _FLAG_H_


// ������ʶ
enum PARA_FLAG
{
    PARA_NORMAL_FLAG = 0x00, // ������ʶ
    PARA_STAR_FLAG = 0x01, // **��ʶ
    PARA_IGNORE_FLAG = 0x04, // �ձ�ʶ

    PARA_ALARM_FLAG = 0x10, // ������ʶ��ȷ���ԣ������ԣ�

    PARA_H_FLAG = 0x100, // H��ʶ
    PARA_L_FLAG = 0x200, // L��ʶ
    PARA_DOULT_FLAG = 0x400, // R��ʶ
};


#endif // _FLAG_H_