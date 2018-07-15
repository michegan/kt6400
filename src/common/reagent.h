#ifndef _REAGENT_H_
#define _REAGENT_H_


#include "libcommon.h"


// 试剂类型
enum REAGENT_TYPE
{
    REAGENT_DT = 0x01, // 稀释液
    REAGENT_LH = 0x02, // HGB溶血剂
};


// 试剂量
namespace Reagent
{
    // 试剂列表
    COMMON_EXPORT QList<int> reagents();

    // 试剂报警
    COMMON_EXPORT bool isEmpty(int reagent);
    COMMON_EXPORT bool isEnough(int reagent);

    // 试剂余量（体积）
    COMMON_EXPORT float remain(int reagent);
    COMMON_EXPORT void setRemain(int reagent, float remain);

    // 试剂总量（体积）
    COMMON_EXPORT float volume(int reagent);
    COMMON_EXPORT void setVolume(int reagent, float volume);

    // 试剂消耗（体积）
    COMMON_EXPORT bool consume(int reagent, float volume);
};


#endif // _REAGENT_H_