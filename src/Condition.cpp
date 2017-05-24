#include "Condition.h"
#include "MutexLock.h"
#include <assert.h>

Condition::Condition(MutexLock &mutex):mutex_(mutex)
{
    CHECK(!pthread_cond_init(&cond_, NULL));//条件变量初始化
}

Condition::~Condition()
{
    CHECK(!pthread_cond_destroy(&cond_));
}


void Condition::wait()
{
    assert(mutex_.isLocking()); //wait前必须上锁
    CHECK(!pthread_cond_wait(&cond_, mutex_.getMutexPtr()));
    //pthread_cond_wait阻塞时解锁，返回时会自动加锁
    mutex_.restoreMutexStatus(); //还原状态
}

void Condition::notify()
{
    CHECK(!pthread_cond_signal(&cond_));
}

void Condition::notifyAll()
{


    CHECK(!pthread_cond_broadcast(&cond_));
}
