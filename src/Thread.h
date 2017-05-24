#ifndef __THREAD_H__
#define __THREAD_H__
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include "Condition.h"
#include "MutexLock.h"
class Thread:boost::noncopyable
{
    public:
	typedef boost::function<void()>threadCallback;
	Thread(threadCallback t);
	~Thread();
	void start();
	void join();
	static void*runInThread(void*);
    private:
	pthread_t threadId_;
	bool isRunning_;
	threadCallback cb_;
};
#endif 
