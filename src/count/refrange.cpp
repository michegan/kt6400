#include <QtDebug>

#include "cache.h"
#include "paraname.h"
#include "refrange.h"


// 参考范围
namespace RefRange
{
    // 本底参考范围
    static bool backgroundLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits)
    {
        lowLimits.appendPara(PARA_WBC, 0, PARA_NORMAL_FLAG);
        lowLimits.appendPara(PARA_RBC, 0, PARA_NORMAL_FLAG);
        lowLimits.appendPara(PARA_PLT, 0, PARA_NORMAL_FLAG);
        lowLimits.appendPara(PARA_HGB, 0, PARA_NORMAL_FLAG);

        highLimits.appendPara(PARA_WBC, 0.2f, PARA_NORMAL_FLAG);
        highLimits.appendPara(PARA_RBC, 0.5f, PARA_NORMAL_FLAG);
        highLimits.appendPara(PARA_PLT, 10, PARA_NORMAL_FLAG);
        highLimits.appendPara(PARA_HGB, 5, PARA_NORMAL_FLAG);

        return true;
    }

    // 正常参考范围
    static bool normalLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits)
    {
        // 所属物种
        QString key1 = sampleInfo.modes.specimodeIds();
        // 所属参考组
        QString refRangeGroup = sampleInfo.refRangeGroup();

        // 提取参考范围信息
        return Cache::refRange(key1, refRangeGroup, lowLimits, highLimits);
    }

    // 获取参考范围
    bool getLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits)
    {
        int bloodMode = sampleInfo.bloodMode();

        if (BLOOD_MODE_BACKGROUND == bloodMode)
        {
            return RefRange::backgroundLimits(sampleInfo, lowLimits, highLimits);
        }
        else if (BLOOD_MODE_QC == bloodMode)
        {
            return false;
        }
        else if (BLOOD_MODE_CALIBRATE == bloodMode)
        {
            return false;
        }
        else
        {
            return RefRange::normalLimits(sampleInfo, lowLimits, highLimits);
        }
    }
}