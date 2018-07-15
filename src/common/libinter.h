#ifndef _LIB_INTER_H_
#define _LIB_INTER_H_


#include "libcommon.h"
#include "event_and_task_data.h"


COMMON_EXPORT void SysDrvDataInit(int fd);
COMMON_EXPORT void SysEventInit();
COMMON_EXPORT void SysTaskInit();
COMMON_EXPORT void InitSysEnv();
COMMON_EXPORT void InitAlarmSet();

COMMON_EXPORT SYS_TIMER* GetSysTimer();
COMMON_EXPORT SYS_AD_BUF* GetSysAdBuf();
COMMON_EXPORT SYS_CT_MAIL* GetSysCtMail();
COMMON_EXPORT SYS_EVENT_BUF* GetSysEventBuf();
COMMON_EXPORT SYS_RUNNING_DATA* GetSysRunningData();
COMMON_EXPORT char* GetSysFtable(unsigned short int len);


#endif // _LIB_INTER_H_
