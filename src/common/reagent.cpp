#include <QMap>

#include "reagent.h"
#include "reagent.h"


// 试剂量
namespace Reagent
{
    // 试剂量
    static QMap<int, float> s_remains;
    static QMap<int, float> s_volumes;

    // 试剂列表
    QList<int> reagents()
    {
        QList<int> reagents;
        reagents.append(REAGENT_DT);
        reagents.append(REAGENT_LH);

        return reagents;
    }

    // 试剂报警
    bool isEmpty(int reagent)
    {
        float remain = Reagent::remain(reagent);
        return (remain <= 0);
    }

    bool isEnough(int reagent)
    {
        float remain = Reagent::remain(reagent);
        float volume = Reagent::volume(reagent);

        return (remain <= volume * 0.05f);
    }

    // 试剂余量（体积）
    float remain(int reagent)
    {
        return s_remains.value(reagent, 0);
    }

    void setRemain(int reagent, float remain)
    {
        if (s_remains.contains(reagent))
        {
            s_remains[reagent] = remain;
        }
        else
        {
            s_remains.insert(reagent, remain);
        }
    }

    // 试剂总量（体积）
    float volume(int reagent)
    {
        return s_volumes.value(reagent, 0);
    }

    void setVolume(int reagent, float volume)
    {
        if (s_volumes.contains(reagent))
        {
            s_volumes[reagent] = volume;
        }
        else
        {
            s_volumes.insert(reagent, volume);
        }
    }

    // 试剂消耗（体积，返回百分比）
    bool consume(int reagent, float volume)
    {
        bool ret = s_remains.contains(reagent);
        if (ret)
        {
            s_remains[reagent] -= volume;
        }
        return ret;
    }
}