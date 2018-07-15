#ifndef _PUNCTION_CONVERT_H_
#define _PUNCTION_CONVERT_H_

#include <QString>

namespace PunctionConvert
{
    // 将半角符号转换为全角符号（中文输入法界面）
    bool convertToChinesePuncForPyInput(int srcPunc, QString& strDst);

    // 将半角符号转换为全角符号（全角符号输入法界面）
    bool convertToChinesePunc(int srcPunc, QString& strDst);
}

#endif //_PUNCTION_CONVERT_H_