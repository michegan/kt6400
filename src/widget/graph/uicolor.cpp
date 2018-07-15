#include "uicolor.h"


// UI颜色
namespace UIColor
{
    // 参数颜色
    QColor paraColor(const Para& para)
    {
        int flag = para.flag;
        if (PARA_H_FLAG == flag)
        {
            return Qt::red;
        }
        else if (PARA_L_FLAG == flag)
        {
            return Qt::blue;
        }
        else
        {
            return Qt::black;
        }
    }
}