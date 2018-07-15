#ifndef _PARA_UNIT_H_
#define _PARA_UNIT_H_


#include "libcommon.h"


// 10^9/L，10^3/uL，10^2/uL，/nL
// 10^12/L，10^6/uL，10^4/uL，/pL
#define U_10_12_L               ("10^12/L")
#define U_10_9_L                ("10^9/L")

#define U_10_6_UL               ("10^6/uL")
//#define U_10_4_UL               ("10^4/uL")
//#define U_10_3_UL               ("10^3/uL")
//#define U_10_2_UL               ("10^2/uL")

#define U_10_0_NL               ("/nL")
#define U_10_0_PL               ("/pL")

#define U_FL                    ("fL")
#define U_UM3                   ("um^3")

#define U_NONE                  ("")
#define U_L_L                   ("L/L")
#define U_ML_L                  ("mL/L")
#define U_PERCENT               ("%")
#define U_10GSD                 ("10GSD")

#define U_G_L                   ("g/L")
#define U_G_DL                  ("g/dL")
#define U_MMOL_L                ("mmol/L")

#define U_PG                    ("pg")
#define U_FMOL                  ("fmol")
#define U_AMOL                  ("amol")


// 参数单位
namespace ParaUnit
{
    // 参数默认单位
    COMMON_EXPORT QString paraUnit(const QString& para);

    // 参数单位转换
    COMMON_EXPORT float toUnit(const QString& from, const QString& to, float value);
};


#endif // _PARA_UNIT_H_