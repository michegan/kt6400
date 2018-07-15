#ifndef _NEW_ALG_H_
#define _NEW_ALG_H_


#include "para.h"
#include "modes.h"
#include "libalg.h"
#include "histinfo.h"


// 算法
namespace Alg
{
    // 算法初始化
    ALG_EXPORT bool init();

    //
    // 算法输入
    //
    ALG_EXPORT void setModes(const Modes& modes);

    ALG_EXPORT void setSysInfo(float lym, float mid, int lym_line, int mid_line);
    ALG_EXPORT void setSysEvtBuf(unsigned short t200, unsigned short t204);

    ALG_EXPORT void setCal(float cl_WBC, float cl_RBC, float cl_HGB, float cl_MCV, float cl_PLT);

    ALG_EXPORT void setMaintanceVal(int L1HIGH, int G1LOW, int L2HIGH, int G2LOW, 
                                    int R1, int R2, int R3, int R4, int WBC, int RBC);

    //
    // 算法计算
    //

    // 算法模拟
    ALG_EXPORT void simulate();

    // 算法计算
    ALG_EXPORT void calculate();
    ALG_EXPORT void calculate(char* wbcDataBuf, long wbcDataLen, char* rbcDataBuf, long rbcDataLen, 
                              char* pltDataBuf, long pltDataLen, int hgbAdVoltage, unsigned int hgbBkVoltage);


    //
    // 算法输出
    //

    // 通道故障
    ALG_EXPORT bool wbcClog();
    ALG_EXPORT bool rbcClog();
    ALG_EXPORT bool hgbError();
    ALG_EXPORT bool hgbBubble();

    ALG_EXPORT int wr_graph_gene();

    // 算法结果
    ALG_EXPORT HistInfo wbcHist();
    ALG_EXPORT HistInfo rbcHist();
    ALG_EXPORT HistInfo pltHist();

    ALG_EXPORT ParaList paraResult();
};


#endif // _NEW_ALG_H_