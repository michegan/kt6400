#ifndef _TRACE_LOG_H_
#define _TRACE_LOG_H_


#include <QObject>

#include "liblog.h"


// ������־���
namespace Log
{
    // �Զ��������Ϣ���
    LOG_EXPORT void syncMessageOutput(QtMsgType type, const char* msg);

    // ��ʼ��
    LOG_EXPORT void init(const QString& logFileName, int maxLogFileLen = 20 * 1024 * 1024);
};


#endif // _TRACE_LOG_H_