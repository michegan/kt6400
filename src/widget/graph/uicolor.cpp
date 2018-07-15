#include "uicolor.h"


// UI��ɫ
namespace UIColor
{
    // ������ɫ
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