#include "libinter.h"


#ifdef _WIN32


void SysDrvDataInit(int fd)
{

}

void SysEventInit()
{

}

void SysTaskInit()
{

}

void InitSysEnv()
{

}

void InitAlarmSet()
{

}

SYS_TIMER* GetSysTimer()
{
    static SYS_TIMER* sysTimer = new SYS_TIMER();
    return sysTimer;
}

SYS_AD_BUF* GetSysAdBuf()
{
    static SYS_AD_BUF* sysAdBuf = new SYS_AD_BUF();
    return sysAdBuf;
}

SYS_CT_MAIL* GetSysCtMail()
{
    static SYS_CT_MAIL* sysCtMail = new SYS_CT_MAIL();
    return sysCtMail;
}

SYS_EVENT_BUF* GetSysEventBuf()
{
    static SYS_EVENT_BUF* sysEventBuf = new SYS_EVENT_BUF();
    return sysEventBuf;
}

SYS_RUNNING_DATA* GetSysRunningData()
{
    static SYS_RUNNING_DATA* sysRunningData = new SYS_RUNNING_DATA();
    return sysRunningData;
}

char* GetSysFtable(unsigned short int len)
{
    static SYS_FTABLE* sysFtTable = new SYS_FTABLE();
    return (char*)(sysFtTable->table + len);
}


#else


// 外部引用，原自libinter.so
extern "C" void SYSDRVDATAINT(int fd);
extern "C" void SYSEVENTINIT(void);
extern "C" void SYSTASKINIT();
extern "C" void INITSYSENV();
extern "C" void INITALARMSET();

extern "C" SYS_TIMER* GETTIMER();
extern "C" SYS_AD_BUF* GETADBUF();
extern "C" SYS_CT_MAIL* GETCTMAIL();
extern "C" SYS_EVENT_BUF* GETSYSENV();
extern "C" EVENT_NOD* SYSEVENTALLOC(void);
extern "C" void SYSEVENTPUT( EVENT_NOD* pEvent );
extern "C" SYS_RUNNING_DATA* GETSYSRUNNINGDATA();
extern "C" char* GETSYSFTABLE(unsigned short int len);


// SYSDRVDATAINT是C语言实现，无法在C++中调用，所以新增SysDrvDataInit完成过渡
void SysDrvDataInit(int fd)
{
    SYSDRVDATAINT(fd);
}

void SysEventInit()
{
    SYSEVENTINIT();
}

void SysTaskInit()
{
    SYSTASKINIT();
}

void InitSysEnv()
{
    INITSYSENV();
}

void InitAlarmSet()
{
    INITALARMSET();
}

SYS_TIMER* GetSysTimer()
{
    return GETTIMER();
}

SYS_AD_BUF* GetSysAdBuf()
{
    return GETADBUF();
}

SYS_CT_MAIL* GetSysCtMail()
{
    return GETCTMAIL();
}

SYS_EVENT_BUF* GetSysEventBuf()
{
    return GETSYSENV();
}

SYS_RUNNING_DATA* GetSysRunningData()
{
    return GETSYSRUNNINGDATA();
}

char* GetSysFtable(unsigned short int len)
{
    return GETSYSFTABLE(len);
}


#endif