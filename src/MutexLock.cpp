#include "MutexLock.h"
MutexLock::MutexLock():isLocking_(false)
{
    CHECK(!pthread_mutex_init(&mutex_,NULL));
}
MutexLock::~MutexLock()
{
    assert(!isLocking());
    CHECK(!pthread_mutex_destroy(&mutex_));
}

void MutexLock::lock()
{
    CHECK(!pthread_mutex_lock(&mutex_))
    isLocking_=true;
}

void MutexLock::unlock()
{
    isLocking_=false;
    CHECK(!pthread_mutex_unlock(&mutex_));
}
