#include <QFile>
#include <QMutex>
#include <QThread>
#include <QDateTime>

#include <stdio.h>

#include "log.h"
#include "logthread.h"


#ifdef _WIN32
    #define snprintf _snprintf
#endif 


// 调试日志输出
namespace Log
{
    // 日志文件定时刷新线程
    static LogThread* s_logThread = 0;

    // 获取线程号
    unsigned long getThreadId()
    {
        return (unsigned long)QThread::currentThreadId();
    }

    // 获取当前时间（文本格式，包含：月-日 时:分:秒）
    void getCurTime(char* buffer, int bufLen)
    {
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();

        memset(buffer, 0, bufLen);
        snprintf(buffer, bufLen, "%d-%d %d:%d:%d %d", date.month(), date.day(), time.hour(), time.minute(), time.second(), time.msec());
    }

    // 日志内容格式化（补充日志类型，线程信息，时间信息）
    void format(char* buffer, int bufLen, const char* msgType, const char* msgData)
    {
        // 线程信息
        int tid = getThreadId();

        // 时间信息
        char time[32] = { 0 };
        Log::getCurTime(time, sizeof(time));

        // 构造完整的日志信息（日志类型，线程号，时间信息，日志内容）
        // 修改解决日志内容输出乱码问题：[INFO T10272] 2-25 23:13:0 936 Database selectRecord "SELECT "F_ID", "F_SID", "F_WORKMODE", "F_SAMPLEMODE", 
        //                               "F_SPECIESMODE", "F_BLOODMODE", "F_ANALYSISMODE", "F_PREPROCESSMODE", "F_SENDER", "F_SEND_TIME", "F_TESTER", 
        //                               "F_TEST_TIME", "F_CHECKER", "F_CHECK_TIììììT??Y??ú?à?b
        memset(buffer, 0, bufLen);
        snprintf(buffer, bufLen - 1, "[%s T%d] %s %s\n", msgType, tid, time, msgData);
    }

    // 自定义调试信息输出
    void syncMessageOutput(QtMsgType type, const char* msg)
    {
        const char* msgType = 0;
        switch (type)
        {
            case QtDebugMsg:
                {
                    msgType = "INFO";
                }
                break;

            case QtWarningMsg:
                {
                    msgType = "WARNING";
                }
                break;

            default:
                {
                    msgType = "ERROR";
                }
                break;
        }

        // 日志内容格式化
        char messageBuffer[256] = { 0 };
        Log::format(messageBuffer, sizeof(messageBuffer), msgType, msg);

        // 日志输出
        QMetaObject::invokeMethod(s_logThread, "recordLog", Qt::QueuedConnection, Q_ARG(const QString&, QString(messageBuffer)));
    }

    // 初始化
    void init(const QString& logFileName, int maxLogFileLen)
    {
        s_logThread = new LogThread(logFileName, maxLogFileLen);
        s_logThread->moveToThread(s_logThread);
        s_logThread->start();
        QMetaObject::invokeMethod(s_logThread, "initLogRecorder", Qt::QueuedConnection);
    }
};