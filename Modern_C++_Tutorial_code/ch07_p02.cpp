#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stdexcept>
#include <utility>
#include <memory>
#include <functional>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>

class mutex
{
    std::atomic<bool> flag{false};

public:
    void lock()
    {
        while (flag.exchange(true, std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void unlock()
    {
        std::atomic_thread_fence(std::memory_order_release);
        flag.store(false, std::memory_order_relaxed);
    }
};

int a = 0;

int main()
{

    mutex mtx_a;

    std::thread t1([&]()
    {
        mtx_a.lock();
        a += 1;
        mtx_a.unlock();
    });
    std::thread t2([&]()
    {
        mtx_a.lock();
        a += 2;
        mtx_a.unlock();
    });

    t1.join();
    t2.join();

    std::cout << a << std::endl;
    return 0;
}
