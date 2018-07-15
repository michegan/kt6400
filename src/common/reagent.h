#ifndef _REAGENT_H_
#define _REAGENT_H_


#include "libcommon.h"


// �Լ�����
enum REAGENT_TYPE
{
    REAGENT_DT = 0x01, // ϡ��Һ
    REAGENT_LH = 0x02, // HGB��Ѫ��
};


// �Լ���
namespace Reagent
{
    // �Լ��б�
    COMMON_EXPORT QList<int> reagents();

    // �Լ�����
    COMMON_EXPORT bool isEmpty(int reagent);
    COMMON_EXPORT bool isEnough(int reagent);

    // �Լ������������
    COMMON_EXPORT float remain(int reagent);
    COMMON_EXPORT void setRemain(int reagent, float remain);

    // �Լ������������
    COMMON_EXPORT float volume(int reagent);
    COMMON_EXPORT void setVolume(int reagent, float volume);

    // �Լ����ģ������
    COMMON_EXPORT bool consume(int reagent, float volume);
};


#endif // _REAGENT_H_