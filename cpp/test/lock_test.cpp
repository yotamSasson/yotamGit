#include <iostream>
#include <thread>
#include <mutex> 

#include "lock.hpp"

using namespace dev;

void ThreadFunction(void);

std::mutex mtx;
int global = 0;

int main ()
{
    std::thread t1(ThreadFunction);
    std::thread t2(ThreadFunction);

    t1.join();
    t2.join();

    return 0;
}

void ThreadFunction(void)
{
    std::thread::id thread_id = std::this_thread::get_id();
    
    for (int i = 0; i < 5; ++i)
    {
        dev::LockGuard<std::mutex> lockGuard(mtx);
        ++global;
        std::cout << "Thread Id is: " << thread_id << " global is: " <<global<< std::endl;

    }
}
