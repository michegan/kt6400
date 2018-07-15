#ifndef _LOG_THREAD_H_
#define _LOG_THREAD_H_


#include <QTimer>
#include <QThread>

#include "liblog.h"

class LogThreadPrivate;


// ��־��¼�߳�
class LOG_EXPORT LogThread : public QThread
{
    Q_OBJECT

public:
    LogThread(const QString& strLogFileName, int iMaxLogFileLen);
    virtual ~LogThread(void);

public slots:
    // ��¼��־
    void recordLog(const QString& strLog);

    // ��ʼ����־ģ��
    void initLogRecorder(void);

private:
    // �ڲ���Ա
    LogThreadPrivate* d;
};


#endif // _LOG_THREAD_H_