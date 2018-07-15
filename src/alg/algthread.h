#ifndef _ALG_THREAD_H_
#define _ALG_THREAD_H_


#include <QThread>

#include "libalg.h"


// 算法线程
class ALG_EXPORT AlgThread : public QThread
{
public:
    AlgThread();
    ~AlgThread();

protected:
    // 线程执行体
    virtual void run();
};


#endif // _ALG_THREAD_H_