#ifndef _LOG_THREAD_H_
#define _LOG_THREAD_H_


#include <QTimer>
#include <QThread>

#include "liblog.h"

class LogThreadPrivate;


// 日志记录线程
class LOG_EXPORT LogThread : public QThread
{
    Q_OBJECT

public:
    LogThread(const QString& strLogFileName, int iMaxLogFileLen);
    virtual ~LogThread(void);

public slots:
    // 记录日志
    void recordLog(const QString& strLog);

    // 初始化日志模块
    void initLogRecorder(void);

private:
    // 内部成员
    LogThreadPrivate* d;
};


#endif // _LOG_THREAD_H_