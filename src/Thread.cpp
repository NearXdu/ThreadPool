#include "Thread.h"

Thread::Thread(threadCallback cb)
    :threadId_(0),
    isRunning_(false),
    cb_(std::move(cb)){}

Thread::~Thread()
{
    if(isRunning_)
    {
	pthread_detach(threadId_);
    }
}
void Thread::start()
{
    pthread_create(&threadId_,NULL,runInThread,this);
    isRunning_=true;
}

void* Thread::runInThread(void * args)
{
    Thread* pt=static_cast<Thread*>(args);
    pt->cb_();//call the callback
    return NULL;
}


void Thread::join()
{
    pthread_join(threadId_,NULL);
    isRunning_=false;
}
