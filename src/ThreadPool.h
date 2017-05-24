#ifndef __THREADPOLL_H__
#define __THREADPOLL_H__
#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <queue>
class ThreadPool : boost::noncopyable
{
    public:
	typedef boost::function<void()>Task;
	ThreadPool(size_t qsize,size_t nthreads);
	~ThreadPool();
	void start();
	void stop();
	void addTask(Task t);
	Task getTask();

	bool isStarted()const{return isStarted_;}
	void runInThread();
	
    private:
	mutable MutexLock mutex_;
	Condition notEmpty_;//blocking queue  full条件变量
	Condition notFull_;//blocking queue empty 条件变量
	size_t queueSize_;//任务队列大小
	std::queue<Task> queue_;//任务队列

	size_t threadsNum_;//线程数目
	boost::ptr_vector<Thread> threads_;//线程池中的线程
	volatile bool isStarted_;

};
#endif
