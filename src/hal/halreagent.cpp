#include <QtDebug>

#include "halfpga.h"
#include "hal.h"
#include "reagent.h"
#include "halreagent.h"


// REAGENT通信
namespace HalReagent
{
    // 试剂余量（体积）
    float remain(int reagent)
    {
        QMap<int, int> maps;
        maps.insert(REAGENT_LH, READ_LH_REMAIN);

        int remain = 0;
        if (maps.contains(reagent))
        {
             HalFpga::query(maps.value(reagent, 0), (char*)&remain, sizeof(remain));
        }

        return remain;
    }

    bool setRemain(int reagent, float remain)
    {
        QMap<int, int> maps;
        maps.insert(REAGENT_LH, SET_LH_REMAIN);

        bool ret = false;
        if (maps.contains(reagent))
        {
            ret = HalFpga::write(maps.value(reagent, 0), remain);
        }

        return ret;
    }

    // 试剂总量（体积）
    float volume(int reagent)
    {
        QMap<int, int> maps;
        maps.insert(REAGENT_LH, READ_LH_REMAIN);

        int volume = 0;
        if (maps.contains(reagent))
        {
            HalFpga::query(maps.value(reagent, 0), (char*)&volume, sizeof(volume));
        }

        return volume;
    }

    bool setVolume(int reagent, float volume)
    {
        QMap<int, int> maps;
        maps.insert(REAGENT_LH, SET_LH_REMAIN);

        bool ret = false;
        if (maps.contains(reagent))
        {
            ret = HalFpga::write(maps.value(reagent, 0), volume);
        }

        return ret;
    }
}