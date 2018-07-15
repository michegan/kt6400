#include "newalg.h"
#include "algthread.h"


AlgThread::AlgThread()

{

}

AlgThread::~AlgThread()
{

}

// 线程执行体
void AlgThread::run()
{
#ifdef _WIN32
    // 算法计算
    Alg::simulate();
#else
    Alg::calculate();
#endif
}