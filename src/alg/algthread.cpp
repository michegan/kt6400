#include "newalg.h"
#include "algthread.h"


AlgThread::AlgThread()

{

}

AlgThread::~AlgThread()
{

}

// �߳�ִ����
void AlgThread::run()
{
#ifdef _WIN32
    // �㷨����
    Alg::simulate();
#else
    Alg::calculate();
#endif
}