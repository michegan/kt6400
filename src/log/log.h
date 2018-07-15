#ifndef _TRACE_LOG_H_
#define _TRACE_LOG_H_


#include <QObject>

#include "liblog.h"


// 调试日志输出
namespace Log
{
    // 自定义调试信息输出
    LOG_EXPORT void syncMessageOutput(QtMsgType type, const char* msg);

    // 初始化
    LOG_EXPORT void init(const QString& logFileName, int maxLogFileLen = 20 * 1024 * 1024);
};


#endif // _TRACE_LOG_H_