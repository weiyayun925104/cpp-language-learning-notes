#include <iostream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>

std::mutex m;

class Data
{
private:
    std::string name;
public:
    Data(const std::string &s) : name(s)
    {
    }
    auto startThreadWithCopyOfThis() const
    {
        using namespace std::literals;
        std::thread t([*this]
        {
            std::this_thread::sleep_for(3s);
            {
                std::unique_lock<std::mutex> l(m);
                std::cout << name << '\n';
            }
        });
        return t;
    }
};

int main()
{
    std::thread t;
    {
        Data d{"c1"};
        t = d.startThreadWithCopyOfThis();
    } // d is no longer valid
    t.join();
}
