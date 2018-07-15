#ifndef _HAL_REAGENT_H_
#define _HAL_REAGENT_H_


#include "libhal.h"


// REAGENTͨ��
namespace HalReagent
{
    // �Լ������������
    HAL_EXPORT float remain(int reagent);
    HAL_EXPORT bool setRemain(int reagent, float remain);

    // �Լ������������
    HAL_EXPORT float volume(int reagent);
    HAL_EXPORT bool setVolume(int reagent, float volume);
};


#endif // _HAL_REAGENT_H_