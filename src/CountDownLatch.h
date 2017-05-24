#ifndef __COUNTDOWNLATCH_H__
#define __COUNTDOWNLATCH_H__
#include "MutexLock.h"
#include "Condition.h"
class CountDownLatch : boost::noncopyable
{
    public:

	explicit CountDownLatch(int count);

	void wait();

	void countDown();

	int getCount() const;

    private:
	mutable MutexLock mutex_;
	Condition condition_;
	int count_;
};

#endif
