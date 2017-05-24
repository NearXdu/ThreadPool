#ifndef __CONDITION_H__
#define __CONDITION_H__
#include "MutexLock.h"
#include <pthread.h>
#include <boost/noncopyable.hpp>
#include <assert.h>
class MutexLock;
class Condition
{
    public:
	Condition(MutexLock &mutex);
	~Condition();
	void wait();
	void notify();
	void notifyAll();
    private:
	pthread_cond_t cond_;
	MutexLock &mutex_;
};



#endif
