#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <execution>
#include <cmath>

class Timer
{
private:
    std::chrono::steady_clock::time_point last;
public:
    Timer()
        : last{std::chrono::steady_clock::now()}
    {
    }
    void printDiff(const std::string &msg = "Timer diff: ")
    {
        auto now{std::chrono::steady_clock::now()};
        std::chrono::duration<double, std::milli> diff{now - last};
        std::cout << msg << diff.count() << "ms\n";
        last = std::chrono::steady_clock::now();
    }
};

int main()
{
    int numElems = 1000;

    struct Data
    {
        double value;  // initial value
        double sqrt;   // parallel computed square root
    };

    // initialize numElems values without square root:
    std::vector<Data> coll;
    coll.reserve(numElems);
    for (int i = 0; i < numElems; ++i)
    {
        coll.push_back(Data{i * 4.37, 0});
    }

    // parallel computation of square roots:
    for_each(std::execution::par,
             coll.begin(), coll.end(),
             [](auto & val)
    {
        val.sqrt = std::sqrt(val.value);
    });
}

