#include <QDir>
#include <QFile>
#include <QMutexLocker>
#include <QStringList>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "log.h"
#include "logthread.h"

// 1M字节
#define MB_BYTE   1024 * 1024


// 日志记录类私有功能类
class LogThreadPrivate
{
public:
    LogThreadPrivate(const QString& strLogFileName, int iMaxLogFileLen);
    ~LogThreadPrivate(void);

    // 初始化日志记录文件
    void initLogFile(void);

    // 检查日志文件所在路径
    bool checkLogFilePath(void);

    // 保存日志到文件
    void saveLogToFile(const QString& strLogData);

    // 备份日志文件
    void backupOldLog(void);

public:
    // 日志文件
    QFile* m_pLogFile;
    QString m_strLogFileName;
    int m_maxLogFileLen;

    // 日志缓冲锁
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

// 初始化日志记录文件
void LogThreadPrivate::initLogFile(void)
{
    printf("LogThreadPrivate::initLogFile, current threadID: %ld\n", (unsigned long)QThread::currentThreadId());

    // 检查日志文件所在路径
    if (!checkLogFilePath())
    {
        return;
    }

    m_pLogFile =  new QFile(m_strLogFileName);
    if (m_pLogFile)
    {
        if (!m_pLogFile->open(QIODevice::ReadWrite | QIODevice::Append))
        {
            // 日志文件打开失败
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

// 检查日志文件所在路径
bool LogThreadPrivate::checkLogFilePath(void)
{
    QDir dirPath;

    // 检测日志文件路径是否存在
    QString strPath = m_strLogFileName.left(m_strLogFileName.lastIndexOf("/"));
    if (!dirPath.exists(strPath))
    {
        // 日志文件所在路径不存在，则创建
        if (!dirPath.mkpath(strPath))
        {
            printf("LogThreadPrivate checkLogFilePath, create log file path fail, %s\n", strPath.toUtf8().constData());
            return false;
        }
    }

    return true;
}

// 保存日志到文件
void LogThreadPrivate::saveLogToFile(const QString& strLogData)
{
    QMutexLocker locker(&m_mutexFile);
    if (strLogData.isEmpty() || NULL == m_pLogFile)
    {
        return;
    }

    // 日志文件大小达到上限的一半时，备份当前日志文件
    int iSize = m_pLogFile->size();
    if ((m_maxLogFileLen / 2) < iSize)
    {
        backupOldLog();
    }

    // 写入日志信息到文件中，从日志文件末尾写入
    m_pLogFile->write(strLogData.toLocal8Bit());
    m_pLogFile->flush();
}

// 备份日志文件
void LogThreadPrivate::backupOldLog(void)
{
    QString strBackupLogFile = m_strLogFileName + ".bak";

    // 先删除原有的日志备份文件
    if (QFile::exists(strBackupLogFile))
    {
        QFile::remove(strBackupLogFile);
    }

    // 将当前日志文件设置为日志备份文件，并释放日志文件资源
    m_pLogFile->rename(strBackupLogFile);
    delete m_pLogFile;
    m_pLogFile = NULL;

    // 创建新的日志文件，用于记录日志
    m_pLogFile = new QFile(m_strLogFileName);
    if (m_pLogFile)
    {
        if (!m_pLogFile->open(QIODevice::ReadWrite | QIODevice::Append))
        {
            // 日志文件打开失败
            delete m_pLogFile;
            m_pLogFile = NULL;
        }
    }
    else
    {
        printf("LogThreadPrivate backupOldLog, create log file failed!\n");
    }
}


// 日志记录线程
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

// 记录日志
void LogThread::recordLog(const QString& strLog)
{
    d->saveLogToFile(strLog);

    // 修改BUG9597，printf非线程安全，将其放在日志线程中统一输出
    // 串口输出
    printf("%s", strLog.toUtf8().constData());
}

// 初始化日志模块
void LogThread::initLogRecorder(void)
{
    d->initLogFile();
}