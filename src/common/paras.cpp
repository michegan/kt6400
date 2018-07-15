#include <QMap>

#include "paras.h"
#include "paraname.h"


// 项目参数
namespace Paras
{
    // 所有质控参数
    QStringList qcParaNames()
    {
        QStringList paras;
        
        paras << PARA_WBC << PARA_LYM_PER << PARA_GRAN_PER << PARA_LYM_NUM << PARA_GRAN_NUM;
        paras << PARA_RBC << PARA_HGB << PARA_HCT << PARA_MCV << PARA_MCH << PARA_MCHC;
        paras << PARA_PLT;

        return paras;
    }

    // 所有校准参数
    QStringList calibrateParaNames()
    {
        QStringList paras;

        paras << PARA_WBC;
        paras << PARA_RBC << PARA_HGB << PARA_MCV << PARA_PLT << PARA_MPV;

        return paras;
    }

    // 分析模式对应的所有报告参数
    QStringList reportParaNames()
    {
        QStringList paras;

        // 全血参数
        paras.append(Paras::wbcReportParaNames());
        paras.append(Paras::rbcReportParaNames());
        paras.append(Paras::pltReportParaNames());

        return paras;
    }

    QStringList wbcReportParaNames()
    {
        QStringList paras;

        paras << PARA_WBC << PARA_LYM_PER << PARA_MID_PER << PARA_GRAN_PER << PARA_LYM_NUM << PARA_MID_NUM << PARA_GRAN_NUM;

        return paras;
    }

    QStringList rbcReportParaNames()
    {
        QStringList paras;

        // 全血参数
        paras << PARA_RBC << PARA_HGB << PARA_HCT << PARA_MCV << PARA_MCH << PARA_MCHC << PARA_RDW_CV << PARA_RDW_SD;

        return paras;
    }

    QStringList pltReportParaNames()
    {
        QStringList paras;

        // 全血参数
        paras << PARA_PLT << PARA_MPV << PARA_PCT << PARA_PDW << PARA_PLCR;

        return paras;
    }

    // 参数描述
    QString paraIds(const QString& paraName)
    {
        static QMap<QString, QString> maps;

        if (maps.isEmpty())
        {
            maps.insert(PARA_WBC, "IDS_WBC");
            maps.insert(PARA_LYM_PER, "IDS_LYM_PER");
            maps.insert(PARA_MID_PER, "IDS_MID_PER");
            maps.insert(PARA_GRAN_PER, "IDS_GRAN_PER");
            maps.insert(PARA_LYM_NUM, "IDS_LYM_NUM");
            maps.insert(PARA_MID_NUM, "IDS_MID_NUM");
            maps.insert(PARA_GRAN_NUM, "IDS_GRAN_NUM");

            maps.insert(PARA_RBC, "IDS_WBC");
            maps.insert(PARA_HGB, "IDS_HGB");
            maps.insert(PARA_HCT, "IDS_HCT");
            maps.insert(PARA_MCV, "IDS_MCV");
            maps.insert(PARA_MCH, "IDS_MCH");
            maps.insert(PARA_MCHC, "IDS_MCHC");
            maps.insert(PARA_RDW_CV, "IDS_RDW_CV");
            maps.insert(PARA_RDW_SD, "IDS_RDW_SD");

            maps.insert(PARA_PLT, "IDS_PLT");
            maps.insert(PARA_MPV, "IDS_MPV");
            maps.insert(PARA_PCT, "IDS_PCT");
            maps.insert(PARA_PDW, "IDS_PDW");
            maps.insert(PARA_PLCR, "IDS_PLCR");
        }

        return maps.value(paraName, paraName);
    }
}