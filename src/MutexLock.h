#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include <iostream>
#include <cstdio>
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <assert.h>

#define CHECK(exp) \
    if(!exp) \
{ \
    fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n",__FILE__, __LINE__); abort();\
}



class MutexLock : public boost::noncopyable
{
    friend class Condition;
    public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();
	bool isLocking() const {
	    return isLocking_;
	}
	pthread_mutex_t *getMutexPtr()
	{
	    return &mutex_;
	}
    private:
	void restoreMutexStatus()
	{
	    isLocking_=true;
	}
	pthread_mutex_t mutex_;
	bool isLocking_;
};


class MutexLockGuard:public boost::noncopyable
{
    public:
	MutexLockGuard(MutexLock &mutex):mutex_(mutex){	mutex_.lock();}//构造时加锁
	~MutexLockGuard()//析构时解锁
	{
	    mutex_.unlock();
	}

    private:
	MutexLock &mutex_;
};


#endif
