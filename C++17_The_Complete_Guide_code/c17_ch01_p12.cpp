#include <iostream>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>

std::mutex m;

thread_local int g_n = 1;

void f()
{
    std::unique_lock<std::mutex> l(m);
    g_n++;
    std::cout << "thread id = " << std::this_thread::get_id() << ", g_n = " << g_n << std::endl;
}

void foo()
{
    thread_local int i=0;
    std::unique_lock<std::mutex> l(m);
    std::cout << "thread id = " << std::this_thread::get_id() << ", i = " << i << std::endl;
    i++;
}

void f2()
{
    foo();
    foo();
}

int main()
{
    g_n++;
    f();    
    std::thread t1(f);
    std::thread t2(f);
    t1.join();
    t2.join();

    f2();
    std::thread t4(f2);
    std::thread t5(f2);
    t4.join();
    t5.join();
    return 0;
}
