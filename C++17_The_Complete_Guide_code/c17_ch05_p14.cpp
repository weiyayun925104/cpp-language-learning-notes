#include <iostream>
#include <vector>
#include <string>
#include <utility>     // for std::invoke()
#include <functional>  // for std::forward()

template<typename Callable, typename... Args>
void call(Callable &&op, Args &&... args)
{
    //...
    std::invoke(std::forward<Callable>(op),    // call passed callable with
                std::forward<Args>(args)...);  // all additional passed args
}


void print(const std::vector<int> &coll)
{
    std::cout << "elems: ";
    for (const auto &elem : coll)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> vals{0, 8, 15, 42, 13, -1, 0};

    call([&vals]
    {
        std::cout << "size: " << vals.size() << '\n';
    });
    call(print, vals);

    call(&decltype(vals)::pop_back, vals);
    call(print, vals);

    call(&decltype(vals)::clear, vals);
    call(print, vals);
}
