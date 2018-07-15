#ifndef _HAL_REAGENT_H_
#define _HAL_REAGENT_H_


#include "libhal.h"


// REAGENT通信
namespace HalReagent
{
    // 试剂余量（体积）
    HAL_EXPORT float remain(int reagent);
    HAL_EXPORT bool setRemain(int reagent, float remain);

    // 试剂总量（体积）
    HAL_EXPORT float volume(int reagent);
    HAL_EXPORT bool setVolume(int reagent, float volume);
};


#endif // _HAL_REAGENT_H_