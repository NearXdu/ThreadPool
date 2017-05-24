# ThreadPool

C++ implementing ThreadPool for practicing

## Reference
https://github.com/chenshuo/muduo

Including following components:
>1.MutexLock : C++ class wrapping up pthread_mutex <br>
>2.MutexLockGuard: C++ RAII trait manage MutexLock<br>
>3.Condition: C++ class wrapping up pthread_cond<br>
>4.CountDownLatch: C++ class implamenting thread safe counter<br>
>5.Thread: C++ class wrapping up pthread_*<br>
>6.ThreadPool: C++ class implamenting thread pool contains a blocking queue(one mutex two cond) and a pointer to thread container(boost::ptr_vector)<br>

## Build

To build this,the follwing needed:
>1.boost<br>
>2.c++0x<br>

```shell
mkdir build
cd build
cmake ..
```
