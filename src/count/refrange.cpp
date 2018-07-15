#include <QtDebug>

#include "cache.h"
#include "paraname.h"
#include "refrange.h"


// �ο���Χ
namespace RefRange
{
    // ���ײο���Χ
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

    // �����ο���Χ
    static bool normalLimits(const SampleInfo& sampleInfo, ParaList& lowLimits, ParaList& highLimits)
    {
        // ��������
        QString key1 = sampleInfo.modes.specimodeIds();
        // �����ο���
        QString refRangeGroup = sampleInfo.refRangeGroup();

        // ��ȡ�ο���Χ��Ϣ
        return Cache::refRange(key1, refRangeGroup, lowLimits, highLimits);
    }

    // ��ȡ�ο���Χ
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