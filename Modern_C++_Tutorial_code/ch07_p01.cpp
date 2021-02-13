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

class ThreadPool
{
public:
    ThreadPool(size_t);

    template<class F, class... Args>
    decltype(auto) enqueue(F &&f, Args &&... args);

    ~ThreadPool();
private:
    std::vector< std::thread > workers;
    std::queue< std::function<void()> > tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads): stop(false)
{
    for(size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back([this]
        {
            for(;;)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);

                    // block current thread
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });

                    // return if queue empty and task finished
                    if(this->stop && this->tasks.empty())
                        return;

                    // otherwise execute the first element of queue
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                // execution
                task();
            }
        });
    }
}

template<class F, class... Args>
decltype(auto) ThreadPool::enqueue(F &&f, Args &&... args)
{
    using return_type = std::invoke_result_t<F, Args...>;

    // fetch task
    auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );

    std::future<return_type> res = task->get_future();

    // critical section
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // avoid add new thread if theadpool is destroyed
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        // add thread to queue
        tasks.emplace([task] { (*task)(); });
    }

    // notify a wait thread
    condition.notify_one();
    return res;
}

// destroy everything
inline ThreadPool::~ThreadPool()
{
    // critical section
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    // wake up all threads
    condition.notify_all();

    for(std::thread &worker : workers)
        worker.join();
}

int main()
{
    ThreadPool pool(4);
    std::vector< std::future<std::string> > results;

    for(int i = 0; i < 8; ++i)
    {
        // add all task to result list
        results.emplace_back(
            pool.enqueue([i]
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return std::string("---thread ") + std::to_string(i) + std::string(" finished.---");
        })
        );
    }

    for(auto &&result : results)
        std::cout << result.get() << std::endl;

    return 0;
}
