#include <QDir>
#include <QFile>
#include <QMutexLocker>
#include <QStringList>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "log.h"
#include "logthread.h"

// 1M�ֽ�
#define MB_BYTE   1024 * 1024


// ��־��¼��˽�й�����
class LogThreadPrivate
{
public:
    LogThreadPrivate(const QString& strLogFileName, int iMaxLogFileLen);
    ~LogThreadPrivate(void);

    // ��ʼ����־��¼�ļ�
    void initLogFile(void);

    // �����־�ļ�����·��
    bool checkLogFilePath(void);

    // ������־���ļ�
    void saveLogToFile(const QString& strLogData);

    // ������־�ļ�
    void backupOldLog(void);

public:
    // ��־�ļ�
    QFile* m_pLogFile;
    QString m_strLogFileName;
    int m_maxLogFileLen;

    // ��־������
    QMutex m_mutexFile;
};

LogThreadPrivate::LogThreadPrivate(const QString& strLogFileName, int iMaxLogFileLen)
    : m_pLogFile(NULL), m_strLogFileName(strLogFileName), m_maxLogFileLen(iMaxLogFileLen)
{

}

LogThreadPrivate::~LogThreadPrivate(void)
{
    if (m_pLogFile)
    {
        m_pLogFile->close();

        delete m_pLogFile;
        m_pLogFile = NULL;
    }
}

// ��ʼ����־��¼�ļ�
void LogThreadPrivate::initLogFile(void)
{
    printf("LogThreadPrivate::initLogFile, current threadID: %ld\n", (unsigned long)QThread::currentThreadId());

    // �����־�ļ�����·��
    if (!checkLogFilePath())
    {
        return;
    }

    m_pLogFile =  new QFile(m_strLogFileName);
    if (m_pLogFile)
    {
        if (!m_pLogFile->open(QIODevice::ReadWrite | QIODevice::Append))
        {
            // ��־�ļ���ʧ��
            delete m_pLogFile;
            m_pLogFile = NULL;
            printf("LogThreadPrivate initLogFile, open log file failed!");
        }
    }
    else
    {
        printf("LogThreadPrivate initLogFile, create log file failed!");
    }
}

// �����־�ļ�����·��
bool LogThreadPrivate::checkLogFilePath(void)
{
    QDir dirPath;

    // �����־�ļ�·���Ƿ����
    QString strPath = m_strLogFileName.left(m_strLogFileName.lastIndexOf("/"));
    if (!dirPath.exists(strPath))
    {
        // ��־�ļ�����·�������ڣ��򴴽�
        if (!dirPath.mkpath(strPath))
        {
            printf("LogThreadPrivate checkLogFilePath, create log file path fail, %s\n", strPath.toUtf8().constData());
            return false;
        }
    }

    return true;
}

// ������־���ļ�
void LogThreadPrivate::saveLogToFile(const QString& strLogData)
{
    QMutexLocker locker(&m_mutexFile);
    if (strLogData.isEmpty() || NULL == m_pLogFile)
    {
        return;
    }

    // ��־�ļ���С�ﵽ���޵�һ��ʱ�����ݵ�ǰ��־�ļ�
    int iSize = m_pLogFile->size();
    if ((m_maxLogFileLen / 2) < iSize)
    {
        backupOldLog();
    }

    // д����־��Ϣ���ļ��У�����־�ļ�ĩβд��
    m_pLogFile->write(strLogData.toLocal8Bit());
    m_pLogFile->flush();
}

// ������־�ļ�
void LogThreadPrivate::backupOldLog(void)
{
    QString strBackupLogFile = m_strLogFileName + ".bak";

    // ��ɾ��ԭ�е���־�����ļ�
    if (QFile::exists(strBackupLogFile))
    {
        QFile::remove(strBackupLogFile);
    }

    // ����ǰ��־�ļ�����Ϊ��־�����ļ������ͷ���־�ļ���Դ
    m_pLogFile->rename(strBackupLogFile);
    delete m_pLogFile;
    m_pLogFile = NULL;

    // �����µ���־�ļ������ڼ�¼��־
    m_pLogFile = new QFile(m_strLogFileName);
    if (m_pLogFile)
    {
        if (!m_pLogFile->open(QIODevice::ReadWrite | QIODevice::Append))
        {
            // ��־�ļ���ʧ��
            delete m_pLogFile;
            m_pLogFile = NULL;
        }
    }
    else
    {
        printf("LogThreadPrivate backupOldLog, create log file failed!\n");
    }
}


// ��־��¼�߳�
LogThread::LogThread(const QString& strLogFileName, int iMaxLogFileLen)
    : QThread(), d(new LogThreadPrivate(strLogFileName, iMaxLogFileLen))
{

}

LogThread::~LogThread(void)
{
    if (d)
    {
        delete d;
        d = NULL;
    }
}

// ��¼��־
void LogThread::recordLog(const QString& strLog)
{
    d->saveLogToFile(strLog);

    // �޸�BUG9597��printf���̰߳�ȫ�����������־�߳���ͳһ���
    // �������
    printf("%s", strLog.toUtf8().constData());
}

// ��ʼ����־ģ��
void LogThread::initLogRecorder(void)
{
    d->initLogFile();
}