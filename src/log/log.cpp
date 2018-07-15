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


// ������־���
namespace Log
{
    // ��־�ļ���ʱˢ���߳�
    static LogThread* s_logThread = 0;

    // ��ȡ�̺߳�
    unsigned long getThreadId()
    {
        return (unsigned long)QThread::currentThreadId();
    }

    // ��ȡ��ǰʱ�䣨�ı���ʽ����������-�� ʱ:��:�룩
    void getCurTime(char* buffer, int bufLen)
    {
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();

        memset(buffer, 0, bufLen);
        snprintf(buffer, bufLen, "%d-%d %d:%d:%d %d", date.month(), date.day(), time.hour(), time.minute(), time.second(), time.msec());
    }

    // ��־���ݸ�ʽ����������־���ͣ��߳���Ϣ��ʱ����Ϣ��
    void format(char* buffer, int bufLen, const char* msgType, const char* msgData)
    {
        // �߳���Ϣ
        int tid = getThreadId();

        // ʱ����Ϣ
        char time[32] = { 0 };
        Log::getCurTime(time, sizeof(time));

        // ������������־��Ϣ����־���ͣ��̺߳ţ�ʱ����Ϣ����־���ݣ�
        // �޸Ľ����־��������������⣺[INFO T10272] 2-25 23:13:0 936 Database selectRecord "SELECT "F_ID", "F_SID", "F_WORKMODE", "F_SAMPLEMODE", 
        //                               "F_SPECIESMODE", "F_BLOODMODE", "F_ANALYSISMODE", "F_PREPROCESSMODE", "F_SENDER", "F_SEND_TIME", "F_TESTER", 
        //                               "F_TEST_TIME", "F_CHECKER", "F_CHECK_TI��������T??Y??��?��?b
        memset(buffer, 0, bufLen);
        snprintf(buffer, bufLen - 1, "[%s T%d] %s %s\n", msgType, tid, time, msgData);
    }

    // �Զ��������Ϣ���
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

        // ��־���ݸ�ʽ��
        char messageBuffer[256] = { 0 };
        Log::format(messageBuffer, sizeof(messageBuffer), msgType, msg);

        // ��־���
        QMetaObject::invokeMethod(s_logThread, "recordLog", Qt::QueuedConnection, Q_ARG(const QString&, QString(messageBuffer)));
    }

    // ��ʼ��
    void init(const QString& logFileName, int maxLogFileLen)
    {
        s_logThread = new LogThread(logFileName, maxLogFileLen);
        s_logThread->moveToThread(s_logThread);
        s_logThread->start();
        QMetaObject::invokeMethod(s_logThread, "initLogRecorder", Qt::QueuedConnection);
    }
};