#include <QMap>
#include <QString>

#include "paraname.h"
#include "paraunit.h"


namespace ParaUnit
{
    // 参数默认单位
    QString paraUnit(const QString& para)
    {
        static QMap<QString, QString> maps;
        if (maps.isEmpty())
        {
            maps.insert(PARA_WBC, U_10_9_L);
            maps.insert(PARA_LYM_PER, U_PERCENT);
            maps.insert(PARA_MID_PER, U_PERCENT);
            maps.insert(PARA_GRAN_PER, U_PERCENT);
            maps.insert(PARA_LYM_NUM, U_10_9_L);
            maps.insert(PARA_MID_NUM, U_10_9_L);
            maps.insert(PARA_GRAN_NUM, U_10_9_L);

            maps.insert(PARA_RBC, U_10_12_L);
            maps.insert(PARA_HGB, U_G_L);
            maps.insert(PARA_HCT, U_NONE);
            maps.insert(PARA_MCV, U_FL);
            maps.insert(PARA_MCH, U_PG);
            maps.insert(PARA_MCHC, U_G_L);
            maps.insert(PARA_RDW_CV, U_NONE);
            maps.insert(PARA_RDW_SD, U_FL);

            maps.insert(PARA_PLT, U_10_9_L);
            maps.insert(PARA_MPV, U_FL);
            maps.insert(PARA_PCT, U_ML_L);
            maps.insert(PARA_PDW, U_10GSD);
            maps.insert(PARA_PLCR, U_PERCENT);
            maps.insert(PARA_PLCC, U_10_9_L);
        }
        return maps.value(para, U_NONE);
    }

    // 参数单位转换
    float toUnit(const QString& from, const QString& to, float value)
    {
        // 
        if (U_10_12_L == from)
        {
            if (U_10_9_L == to)
            {
                return (value * 1000);
            }
            else if (U_10_6_UL == to)
            {
                return (value);
            }
        }
        else if (U_10_9_L == from)
        {
            if (U_10_12_L == to)
            {
                return (value * 0.001);
            }
            else if (U_10_6_UL == to)
            {
                return (value * 0.001);
            }
        }
        else if (U_10_6_UL == from)
        {
            if (U_10_12_L == to)
            {
                return (value);
            }
            else if (U_10_9_L == to)
            {
                return (value * 1000);
            }
        }

        // 
        else if (U_10_0_NL == from)
        {
            if (U_10_0_PL == to)
            {
                return (value * 0.001);
            }
        }
        else if (U_10_0_PL == from)
        {
            if (U_10_0_NL == to)
            {
                return (value * 1000);
            }
        }

        // 
        else if (U_FL == from)
        {
            if (U_UM3 == to)
            {
                return (value);
            }
        }
        else if (U_UM3 == from)
        {
            if (U_FL == to)
            {
                return (value);
            }
        }

        // 
        else if (U_NONE == from)
        {
            if (U_L_L == to)
            {
                return (value);
            }
            else if (U_ML_L == to)
            {
                return (value * 1000);
            }
            else if (U_PERCENT == to)
            {
                return (value * 100);
            }
            else if (U_10GSD == to)
            {
                return (value);
            }
        }
        else if (U_L_L == from)
        {
            if (U_NONE == to)
            {
                return (value);
            }
            else if (U_ML_L == to)
            {
                return (value * 1000);
            }
            else if (U_PERCENT == to)
            {
                return (value * 100);
            }
            else if (U_10GSD == to)
            {
                return (value);
            }
        }
        else if (U_ML_L == from)
        {
            if (U_L_L == to)
            {
                return (value * 0.001);
            }
            else if (U_NONE == to)
            {
                return (value * 0.001);
            }
            else if (U_PERCENT == to)
            {
                return (value * 0.1);
            }
            else if (U_10GSD == to)
            {
                return (value);
            }
        }
        else if (U_PERCENT == from)
        {
            if (U_L_L == to)
            {
                return (value * 0.01);
            }
            else if (U_ML_L == to)
            {
                return (value * 10);
            }
            else if (U_NONE == to)
            {
                return (value * 0.01);
            }
            else if (U_10GSD == to)
            {
                return (value);
            }
        }
        else if (U_10GSD == from)
        {
            if (U_L_L == to)
            {
                return (value);
            }
            else if (U_ML_L == to)
            {
                return (value);
            }
            else if (U_PERCENT == to)
            {
                return (value);
            }
            else if (U_NONE == to)
            {
                return (value);
            }
        }

        // 
        if (U_G_L == from)
        {
            if (U_G_DL == to)
            {
                return (value * 1000);
            }
            else if (U_MMOL_L == to)
            {
                return (value);
            }
        }
        else if (U_G_DL == from)
        {
            if (U_G_L == to)
            {
                return (value);
            }
            else if (U_MMOL_L == to)
            {
                return (value);
            }
        }
        else if (U_MMOL_L == from)
        {
            if (U_G_L == to)
            {
                return (value);
            }
            else if (U_G_DL == to)
            {
                return (value);
            }
        }

        // 
        if (U_PG == from)
        {
            if (U_FMOL == to)
            {
                return (value);
            }
            else if (U_AMOL == to)
            {
                return (value);
            }
        }
        else if (U_FMOL == from)
        {
            if (U_PG == to)
            {
                return (value);
            }
            else if (U_AMOL == to)
            {
                return (value);
            }
        }
        else if (U_AMOL == from)
        {
            if (U_FMOL == to)
            {
                return (value);
            }
            else if (U_PG == to)
            {
                return (value);
            }
        }

        return value;
    }
}