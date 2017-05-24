#include "ThreadPool.h"
ThreadPool::ThreadPool(size_t q,size_t n)
    :mutex_(),
     notEmpty_(mutex_),
     notFull_(mutex_),
     queueSize_(q),
     threadsNum_(n),
     isStarted_(false)
{}
ThreadPool::~ThreadPool()
{
    if(isStarted_)
    {
	stop();
    }
}


void ThreadPool::stop()
{	
    {
	MutexLockGuard lock(mutex_);
	isStarted_ = false;
	notEmpty_.notifyAll(); //激活所有的线程

    }
    for_each(threads_.begin(),
	    threads_.end(),
	    boost::bind(&Thread::join, _1));

}
void ThreadPool::addTask(Task t)
{
    if(threads_.empty())
    {
	t();
    }
    else
    {

	MutexLockGuard lock(mutex_);
	while(queue_.size()>=queueSize_&&isStarted_)
	    notFull_.wait();
	if(!isStarted_)
	    return ;

	queue_.push(std::move(t));
	notEmpty_.notify();
    }
}

ThreadPool::Task ThreadPool::getTask()
{
    MutexLockGuard lock(mutex_);
    while(queue_.empty()&&isStarted_)
    {
	notEmpty_.wait();
    }
    Task t;
    if(!queue_.empty())
    {
	assert(!queue_.empty());
	t=queue_.front();
	queue_.pop();
	notFull_.notify();
    }

    return t;
}

void ThreadPool::runInThread()
{
    while(isStarted_)
    {
	//	std::cout<<"hello runinThread"<<std::endl;
	Task t(getTask());//will blocked until "add" ops
	//assert(t!=NULL);
	if(t)
	{
	    t();//run
	}
    }
}

void ThreadPool::start()
{
    isStarted_=true;
    threads_.reserve(threadsNum_);
    for(size_t i=0;i<threadsNum_;++i)
    {
	threads_.push_back(
		new Thread(boost::bind(
			&ThreadPool::runInThread,this)));

	threads_[i].start();
    }

}
