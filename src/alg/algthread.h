#ifndef _ALG_THREAD_H_
#define _ALG_THREAD_H_


#include <QThread>

#include "libalg.h"


// �㷨�߳�
class ALG_EXPORT AlgThread : public QThread
{
public:
    AlgThread();
    ~AlgThread();

protected:
    // �߳�ִ����
    virtual void run();
};


#endif // _ALG_THREAD_H_