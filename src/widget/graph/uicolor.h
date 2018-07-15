#ifndef _UI_COLOR_H_
#define _UI_COLOR_H_


#include <QColor>

#include "para.h"
#include "libwidget.h"


// UI颜色
namespace UIColor
{
    // 参数颜色
    WIDGET_EXPORT QColor paraColor(const Para& para);
};


#endif // _UI_COLOR_H_