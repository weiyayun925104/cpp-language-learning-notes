#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

int main()
{
    int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
    std::list<int> yadayada(vals, vals + 10);
    std::list<int> etcetera(vals, vals + 10);

    auto outint = [](int n)
    {
        std::cout << n << " ";
    };
    std::cout << "Original lists:\n";
    std::for_each(yadayada.begin(), yadayada.end(), outint);
    std::cout << std::endl;
    std::for_each(etcetera.begin(), etcetera.end(), outint);
    std::cout << std::endl;

    yadayada.remove_if([](int x)
    {
        return x > 100;
    });
    etcetera.remove_if([](int x)
    {
        return x > 200;
    });

    std::cout << "Trimmed lists:\n";
    std::for_each(yadayada.begin(), yadayada.end(), outint);
    std::cout << std::endl;
    std::for_each(etcetera.begin(), etcetera.end(), outint);
    std::cout << std::endl;

    return 0;
}
