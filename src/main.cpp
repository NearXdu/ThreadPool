#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "CountDownLatch.h"
#include "ThreadPool.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
//using namespace std;

CountDownLatch latch(2);
void task()
{
    std::cout<<"hello world"<<std::endl;
    latch.countDown();
}
void task2(int i)
{
    std::cout<<"hello world "<<i<<std::endl;

    latch.countDown();
}
int main()
{
    ThreadPool p(10,2);//10 queuesize 2 threads

    p.start();
    p.addTask(task);
    p.addTask(boost::bind(task2,3));

    //p.addTask(boost::bind(&CountDownLatch::countDown,&latch));

    latch.wait();

    return 0;
}

