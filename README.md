# ThreadPool

C++ implementing ThreadPool for practicing

## Reference
https://github.com/chenshuo/muduo

Including following components:
>1.MutexLock : C++ class wrapping up pthread_mutex
>2.MutexLockGuard: C++ RAII trait manage MutexLock
>3.Condition: C++ class wrapping up pthread_cond
>4.CountDownLatch: C++ class implamenting thread safe counter
>5.Thread: C++ class wrapping up pthread_*
>6.ThreadPool: C++ class implamenting thread pool contains a blocking queue(one mutex two cond) and a pointer to thread container(boost::ptr_vector)

## Build

To build this,the follwing needed:
>1.boost
>2.c++0x

```shell
mkdir build
cd build
cmake ..
```
